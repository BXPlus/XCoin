//
// Created by kevin on 11/13/21.
//
#include "node.h"

XNode::Node::Node() {
    this->blockchain = Blockchain();
    blockchain.appendBlock(blockchain.generateNextBlock("test block",0,0,"abcd"));
    this->peers = std::map<std::string, XNode::XNodeClient>();
}

/**
* Function called to start up a node, initiate peer-discovery & synchronisation
* @param dnsSeedPeers is a list of DNS seed node addresses to attempt initial connections
*/
void XNode::Node::RunNode(const std::vector<std::string>& dnsSeedPeers) {
    if (this->sdkInstance == nullptr)
        this->Shutdown("No SDK instance set to handle callbacks");
    std::string server_address("0.0.0.0:50051");
    ::grpc::EnableDefaultHealthCheckService(true);
    ::grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, ::grpc::InsecureServerCredentials());
    builder.RegisterService(static_cast<xcoin::interchange::XNodeControl::Service *>(this));
    builder.RegisterService(static_cast<xcoin::interchange::XNodeSync::Service *>(this));
    this->server = builder.BuildAndStart();
    spdlog::info("Server listening on " + server_address);
    sdkInstance->onStatusChanged(XNodeSDK::XNodeStatus::WaitingForDNSS);
    bool couldPerformHandshakeWithDNSS = false;
    loadDataFromDisk();
    for (const std::string &peer: dnsSeedPeers)
        couldPerformHandshakeWithDNSS |= this->AttemptPeerConnection(peer);
    if (!couldPerformHandshakeWithDNSS && !dnsSeedPeers.empty())
        this->Shutdown("Could not establish connection with any DNSS");
    else sdkInstance->onStatusChanged(XNodeSDK::XNodeStatus::SyncingBlockchain);
    server->Wait();
}

/**
* Function called to shut down a node due to an error: terminates the gRPC thread gracefully and saves data on disk
*/
void XNode::Node::Shutdown(const std::string& reason) {
    sdkInstance->onStatusChanged(XNodeSDK::XNodeStatus::TerminatedWithError);
    spdlog::info(reason + " : node will shut down");
    saveDataOnDisk();
    this->server->Shutdown();
    exit(EXIT_SUCCESS);
}

/**
* Function called to persist node data on disk to speed up subsequent launches
* Saves peers and chain in two different savefiles
*/
void XNode::Node::saveDataOnDisk() {
    spdlog::debug(std::string("Will save peers on disk"));
    Archive localPeers = Archive(XNODE_PEERS_SAVE_PATH);
    Archive localChain = Archive(XNODE_BLOCKCHAIN_SAVE_PATH);
    xcoin::interchange::DNSHandshake encodedPeers;
    for (std::pair<const std::basic_string<char>, XNodeClient> &peer: this->peers) {
        xcoin::interchange::DNSEntry *entry = encodedPeers.add_entries();
        entry->set_ipport(peer.first);
        entry->set_publickey(peer.second.publicKey);
    }
    localPeers.saveData(encodedPeers.SerializeAsString());
    std::string encodedChain = XNode::Interface::exportChain(this->blockchain.toBlocks());
    localChain.saveData(encodedChain);
}

/**
* Function called to load savefile data from disk on launch
* Peer list and blockchain are updated from the save file contents
*/
void XNode::Node::loadDataFromDisk() {
    Archive localDataArchive = Archive(XNODE_PEERS_SAVE_PATH);
    Archive localChainArchive = Archive(XNODE_BLOCKCHAIN_SAVE_PATH);
    if (localDataArchive.exists()){
        std::string encodedData = localDataArchive.loadData();
        xcoin::interchange::DNSHandshake loadedPeers;
        loadedPeers.ParseFromString(encodedData);
        for (const xcoin::interchange::DNSEntry& peer: loadedPeers.entries()){
            std::cout << peer.ipport() << std::endl;
            if (handleIncomingPeerData(peer))
                spdlog::debug("Reconnected to peer from cache: " + peer.ipport());
        }
    }
    if (localChainArchive.exists()){
        std::string encodedChain = localChainArchive.loadData();
        XNode::Interface::importChain(encodedChain);
    }
}


/**
* Callback function executed by gRPC to process incoming Ping requests from peers
* Add the peer to the list of known nodes if necessary and replies with ping data
*/
::grpc::Status XNode::Node::Ping(::grpc::ServerContext *context, const ::xcoin::interchange::PingHandshake *request,
                                 ::xcoin::interchange::PingHandshake *response) {
    spdlog::debug("Ping received from " + context->peer());
    if (this->peers.count(context->peer()) == 0) {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(context->peer(),
                                                                     grpc::InsecureChannelCredentials());
        this->peers[context->peer()] = XNodeClient(channel);
    }
    response->set_data(request->data());
    return ::grpc::Status::OK;
}

/**
* Callback function executed by gRPC to process incoming DNS Sync requests from peers
* Handles incoming peers and replies with own known peers
*/
::grpc::Status
XNode::Node::DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request,
                             ::xcoin::interchange::DNSHandshake *response) {
    spdlog::debug("DNS sync requested by " + context->peer());
    for (const xcoin::interchange::DNSEntry &remotePeer: request->entries())
        handleIncomingPeerData(remotePeer);
    for (const std::pair<const std::basic_string<char>, XNodeClient> &x: this->peers)
        if (x.first != context->peer()) {
            xcoin::interchange::DNSEntry *entry = response->add_entries();
            entry->set_ipport(x.first);
            entry->set_publickey(x.second.publicKey);
        }
    return ::grpc::Status::OK;
}

/**
* Callback function executed by gRPC to process incoming peer change notifications from peers
* Handles new peer data and sends back to confirm
*/
::grpc::Status
XNode::Node::NotifyPeerChange(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request,
                              ::xcoin::interchange::DNSEntry *response) {
    this->handleIncomingPeerData(*request);
    response->CopyFrom(*request);
    return ::grpc::Status::OK;
}

/**
* Callback function executed by gRPC to process incoming header sync requests from peers
* Handles new peer data and sends back to confirm
*/
::grpc::Status
XNode::Node::HeaderFirstSync(::grpc::ServerContext *context, const ::xcoin::interchange::GetHeaders *request,
                             ::xcoin::interchange::Headers *response) {
    spdlog::debug("Header first sync requested by " + context->peer());
    if (request->stophash() == "0"){

    }
    for (int i = 1; i < request->blockheaderhashes_size(); i++)
        if (request->blockheaderhashes(i) != this->blockchain.toBlocks()[i].headerHash) {
            spdlog::debug("header desync detected");
            // TODO: Use the response to construct the new blockchain, right now we will just import the blockchain from the peer and check which one is valid.
        }
    for (const Block &block: this->blockchain.toBlocks()) {
        xcoin::interchange::Header *header = response->add_headers();
        header->set_previousblockheaderhash(block.previousHeaderHash);
        header->set_merkleroothash(block.merkle_root_hash);
        header->set_time(block.timestamp);
    }
    return ::grpc::Status::OK;
}

::grpc::Status XNode::Node::GetBlock(::grpc::ServerContext *context, const ::xcoin::interchange::Header *request,
                                     ::xcoin::interchange::Block *response) {
    for (const Block &block: this->blockchain.toBlocks())
        if (block.previousHeaderHash == request->previousblockheaderhash() &&
            block.merkle_root_hash == request->merkleroothash() &&
            block.timestamp == request->time()) {
            response->CopyFrom(XNode::Interface::encodeBlock(block));
            return ::grpc::Status::OK;
        }
    return ::grpc::Status::CANCELLED;
}

::grpc::Status
XNode::Node::GetBlockchain(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request,
                           ::xcoin::interchange::Blockchain *response) {
    xcoin::interchange::Blockchain *blockchainResponse = response->New();
    for (const Block &block: this->blockchain.toBlocks()) {
        xcoin::interchange::Block *encodedBlock = blockchainResponse->add_blocks();
        encodedBlock->CopyFrom(XNode::Interface::encodeBlock(block));
    }
    return ::grpc::Status::OK;
}

/**
* Function called to try to connect to a remote peer
* If ping request is successful, DNS sync is performed, and ping is calculated
* @param peerAddress is an ipv4 or ipv6 address of a potential remote node to connect to
* @returns true if the connection and handshake was successful
*/
bool XNode::Node::AttemptPeerConnection(const std::string &peerAddress) {
    spdlog::debug("Will attempt to connect to new peer " + peerAddress);
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(peerAddress, grpc::InsecureChannelCredentials());
    this->peers[peerAddress] = XNode::XNodeClient(channel);
    ::grpc::ClientContext pingContext;
    xcoin::interchange::PingHandshake pingRequest;
    xcoin::interchange::PingHandshake pingReply;
    pingRequest.set_data("Hello!");
    clock_t start = clock();
    ::grpc::Status pingStatus = this->peers[peerAddress].controlStub->Ping(&pingContext, pingRequest, &pingReply);
    clock_t end = clock();
    if (pingStatus.ok() && pingReply.data() == pingRequest.data()) {
        spdlog::info("Successfully established connection with " + peerAddress + " with ping: " +
                     std::to_string(((float) end - start) / CLOCKS_PER_SEC) + "s");
        xcoin::interchange::DNSHandshake dnsRequest;
        xcoin::interchange::DNSHandshake dnsReply;
        for (std::pair<const std::basic_string<char>, XNodeClient> &peer: peers)
            if (peer.first != peerAddress){
                xcoin::interchange::DNSEntry *entry = dnsRequest.add_entries();
                entry->set_ipport(peer.first);
                entry->set_publickey(peer.second.publicKey);
            }
        ::grpc::ClientContext dnsContext;
        ::grpc::Status dnsStatus = this->peers[peerAddress].controlStub->DNSSyncPeerList(&dnsContext, dnsRequest,
                                                                                         &dnsReply);
        if (dnsStatus.ok()) {
            for (const xcoin::interchange::DNSEntry &remotePeer: dnsReply.entries())
                this->handleIncomingPeerData(remotePeer);
            spdlog::info("Successfully synced DNS peers with " + peerAddress);
            saveDataOnDisk();
            sdkInstance->onPeerListChanged();
            if(AttemptHeaderSync(peerAddress))
                sdkInstance->onStatusChanged(XNodeSDK::XNodeStatus::Ready);
            return true;
        } else spdlog::warn("DNS peer sync with " + peerAddress + " failed");
    } else {
        spdlog::warn("Connection with peer " + peerAddress + " failed");
        this->peers.erase(peerAddress);
    }
    return false;
}

/**
* Function called to initiate blockchain sync with a peer, using header first method
* Block headers are divided into batches and compared with the peer's remote branch
* @param peerAddress is an ipv4 or ipv6 address of the node to sync headers with
* @returns true if the blockchain could be resolved on both ends
*/
bool XNode::Node::AttemptHeaderSync(const std::string &peerAddress) {
    spdlog::debug("Will attempt to sync headers with " + peerAddress);
    std::vector<Block> blockVector = this->blockchain.toBlocks();
    std::reverse(blockVector.begin(), blockVector.end());
    for (size_t i = 0; i < blockVector.size(); i += 200){
        std::vector<Block>::const_iterator first = blockVector.begin() + i;
        std::vector<Block>::const_iterator last = blockVector.begin() +  std::min(blockVector.size(), i + 200);
        std::vector<Block> blockBatch(first,last);
        ::grpc::ClientContext headerFirstSyncContext;
        xcoin::interchange::GetHeaders headerFirstSyncRequest;
        headerFirstSyncRequest.set_version(XNODE_VERSION_INITIAL);
        headerFirstSyncRequest.set_hashcount(last-first);
        if (i+200 < blockVector.size())
            headerFirstSyncRequest.set_stophash("0");
        else headerFirstSyncRequest.set_stophash(blockBatch.back().headerHash);
        for (Block block: blockBatch){
            std::string* headerHash = headerFirstSyncRequest.add_blockheaderhashes();
            headerHash = &block.headerHash;
        }
        xcoin::interchange::Headers headerFirstSyncReply;
        ::grpc::Status headerFirstSyncStatus = this->peers[peerAddress].syncStub->HeaderFirstSync(
                &headerFirstSyncContext, headerFirstSyncRequest, &headerFirstSyncReply);
        if (headerFirstSyncStatus.ok()) {
            // TODO: Handle reply
            break;
        }else return false;
    }
    return true;
}

/**
* Function called to process incoming peer data
* If the peer is known, resolve data conflicts if any, otherwise try to connect and add to known peers
* @param remotePeer the incoming peer data
* @param peerStub the control stub of the remote peer to follow up with other requests if necessary
*/
bool XNode::Node::handleIncomingPeerData(const xcoin::interchange::DNSEntry &remotePeer) {
    if (this->peers.count(remotePeer.ipport()) != 0) {
        if (this->peers[remotePeer.ipport()].publicKey != remotePeer.publickey()) {
            if (this->peers[remotePeer.ipport()].publicKey == XNODE_PUBLICADDR_UNKNOWN) {
                std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(remotePeer.ipport(),grpc::InsecureChannelCredentials());
                this->peers[remotePeer.ipport()] = XNodeClient(channel);
            } else if (remotePeer.ipport() == XNODE_PUBLICADDR_UNKNOWN) {
                ::grpc::ClientContext context;
                xcoin::interchange::DNSEntry notificationRequest;
                xcoin::interchange::DNSEntry notificationReply;
                this->peers[remotePeer.ipport()].controlStub->NotifyPeerChange(&context, notificationRequest,
                                                                         &notificationReply);
                spdlog::debug("Notified peer about additional details for " + remotePeer.ipport());
            } //TODO: Else ask peer directly for its details
        }
        return true;
    } else {
        return this->AttemptPeerConnection(remotePeer.ipport());
    }
}

