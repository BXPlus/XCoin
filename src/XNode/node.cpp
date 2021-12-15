//
// Created by kevin on 11/13/21.
//
#include "node.h"

xcoin::Node::Node() {
    this->blockchain = Blockchain();
    this->peers = std::map<std::string, xcoin::XNodeClient>();
    for (int i = 0; i < 50; i++) {
        this->blockchain.appendBlock(this->blockchain.generateNextBlock("Hello" + std::to_string(i), i+1, 0, ""));
    }
    std::cout << this->blockchain.getLatestBlock().hash << std::endl;

}

/**
* Function called to start up a node, initiate peer-discovery & synchronisation
* @param dnsSeedPeers is a list of DNS seed node addresses to attempt initial connections
*/
void xcoin::Node::RunNode(const std::vector<std::string>& dnsSeedPeers) {
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
    // loadDataFromDisk(); //TODO: READD ONCE READY
    for (const std::string &peer: dnsSeedPeers)
        couldPerformHandshakeWithDNSS |= this->AttemptPeerConnection(peer);
    if (!couldPerformHandshakeWithDNSS && !dnsSeedPeers.empty())
        this->Shutdown("Could not establish connection with any DNSS");
    else sdkInstance->onStatusChanged(XNodeSDK::XNodeStatus::SyncingBlockchain);
    server.release();
}

/**
* Function called to shut down a node due to an error: terminates the gRPC thread gracefully and saves data on disk
*/
void xcoin::Node::Shutdown(const std::string& reason) {
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
void xcoin::Node::saveDataOnDisk() {
    spdlog::debug(std::string("Will save data on disk"));
    Archive localPeers = Archive(XNODE_PEERS_SAVE_PATH);
    Archive localChain = Archive(XNODE_BLOCKCHAIN_SAVE_PATH);
    xcoin::interchange::DNSHandshake encodedPeers;
    for (std::pair<const std::basic_string<char>, XNodeClient> &peer: this->peers) {
        xcoin::interchange::DNSEntry *entry = encodedPeers.add_entries();
        entry->set_ipport(peer.first);
        entry->set_publickey(peer.second.publicKey);
    }
    localPeers.saveData(encodedPeers.SerializeAsString());
    std::string encodedChain = xcoin::interface::exportChain(this->blockchain.toBlocks());
    localChain.saveData(encodedChain);
}

/**
* Function called to load savefile data from disk on launch
* Peer list and blockchain are updated from the save file contents
*/
void xcoin::Node::loadDataFromDisk() {
    Archive localDataArchive = Archive(XNODE_PEERS_SAVE_PATH);
    Archive localChainArchive = Archive(XNODE_BLOCKCHAIN_SAVE_PATH);
    if (localDataArchive.exists()){
        std::string encodedData = localDataArchive.loadData();
        xcoin::interchange::DNSHandshake loadedPeers;
        loadedPeers.ParseFromString(encodedData);
        for (const xcoin::interchange::DNSEntry& peer: loadedPeers.entries()){
            if (handleIncomingPeerData(peer))
                spdlog::debug("Reconnected to peer from cache: " + peer.ipport());
        }
    }
    if (localChainArchive.exists()){
        std::string encodedChain = localChainArchive.loadData();
        xcoin::interface::importChain(encodedChain);
    }
}


/**
* Callback function executed by gRPC to process incoming Ping requests from peers
* Add the peer to the list of known nodes if necessary and replies with ping data
*/
::grpc::Status xcoin::Node::Ping(::grpc::ServerContext *context, const ::xcoin::interchange::PingHandshake *request,
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
xcoin::Node::DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request,
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
xcoin::Node::NotifyPeerChange(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request,
                              ::xcoin::interchange::DNSEntry *response) {
    this->handleIncomingPeerData(*request);
    response->CopyFrom(*request);
    return ::grpc::Status::OK;
}

::grpc::Status xcoin::Node::PingPongSync(::grpc::ServerContext *context, const ::xcoin::interchange::PingPong *request,
                                         ::xcoin::interchange::PingPong *response) {
    ::spdlog::warn("RECEIVED PING PONG");
    if (this->blockchain.length - request->height()<0){ // We need to initiate sync from here as our branch is late
        PingPongStatus stat = this->pingPongStatusForProps(request->height(), this->blockchain.length, request->lasthash(),
                                                           this->blockchain.getLatestBlock().headerHash,false);
        this->AttemptBlockchainSync(context->peer(), stat, request->height());
    }
    response->set_height(this->blockchain.length);
    response->set_lasthash(this->blockchain.getLatestBlock().headerHash);
    return ::grpc::Status::OK;
}

/**
* Callback function executed by gRPC to process incoming header sync requests from peers
* Handles new peer data and sends back to confirm
*/
::grpc::Status
xcoin::Node::HeaderFirstSync(::grpc::ServerContext *context, const ::xcoin::interchange::GetHeaders *request,
                             ::xcoin::interchange::Headers *response) {
    std::vector<Block> localBlocks = this->blockchain.toBlocks();
    std::reverse(localBlocks.begin(), localBlocks.end());
    if (request->stophash() == "0"){
        for (const Block& block : localBlocks){
            xcoin::interchange::Header *header = response->add_headers();
            header->set_merkleroothash(block.merkle_root_hash);
            header->set_blockheaderhash(block.headerHash);
            header->set_time(block.timestamp);
        }
    }
    return ::grpc::Status::OK;
}

::grpc::Status xcoin::Node::GetBlockchainFromHeight(::grpc::ServerContext *context,
                                                    const ::xcoin::interchange::GetBlockchainFromHeightRequest *request,
                                                    ::xcoin::interchange::Blockchain *response) {
    std::vector<Block> localBlocks = this->blockchain.toBlocks();
    if (request->startheight() > localBlocks.size())
        return ::grpc::Status::CANCELLED;
    std::cout << request->startheight() << " " << localBlocks.size() << std::endl;
    for (int i = request->startheight(); i < localBlocks.size(); i++){
        auto newBlock = response->add_blocks();
        std::cout << "Adding block " << localBlocks[i].data << std::endl;
        std::cout << "Block hash: " << localBlocks[i].headerHash << std::endl;
        newBlock->CopyFrom(xcoin::interface::encodeBlock(localBlocks[i]));
    }
    return ::grpc::Status::OK;
}


/**
* Function called to try to connect to a remote peer
* If ping request is successful, DNS sync is performed, and ping is calculated
* @param peerAddress is an ipv4 or ipv6 address of a potential remote node to connect to
* @returns true if the connection and handshake was successful
*/
bool xcoin::Node::AttemptPeerConnection(const std::string &peerAddress) {
    spdlog::debug("Will attempt to connect to new peer " + peerAddress);
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(peerAddress, grpc::InsecureChannelCredentials());
    this->peers[peerAddress] = xcoin::XNodeClient(channel);
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
            std::pair<xcoin::Node::PingPongStatus, int> pingPongStatus = AttemptPingPongSync(peerAddress);
            if(AttemptBlockchainSync(peerAddress, pingPongStatus.first, pingPongStatus.second)){
                this->peers[peerAddress].syncSuccess = true;
                spdlog::info("Successfully synced blockchain with " + peerAddress);
                std::cout << this->blockchain.getLatestBlock().hash << std::endl;
                saveDataOnDisk();
                sdkInstance->onStatusChanged(XNodeSDK::XNodeStatus::Ready);
            }
            return true;
        } else spdlog::warn("DNS peer sync with " + peerAddress + " failed");
    } else {
        spdlog::warn("Connection with peer " + peerAddress + " failed");
        this->peers.erase(peerAddress);
    }
    return false;
}

/**
* Small sync utility to detect early on that two nodes are synced without exchanging header lists
* Blockchain height and last hash are compared with peer node
* @param peerAddress is an ipv4 or ipv6 address of the node to ping pong sync with
* @returns a pair with 1 the status depending on the differences in height and last hash and 2 the remote peer's chain height
*/
std::pair<xcoin::Node::PingPongStatus, int> xcoin::Node::AttemptPingPongSync(const std::string &peerAddress) {
    ::grpc::ClientContext pingPongContext;
    xcoin::interchange::PingPong pingPongRequest;
    xcoin::interchange::PingPong pingPongReply;
    pingPongRequest.set_height(this->blockchain.length);
    pingPongRequest.set_lasthash(this->blockchain.getLatestBlock().headerHash);
    ::grpc::Status pingPongStatus = this->peers[peerAddress].syncStub->PingPongSync(&pingPongContext, pingPongRequest, &pingPongReply);
    return {this->pingPongStatusForProps(pingPongReply.height(), pingPongRequest.height(), pingPongReply.lasthash(), pingPongRequest.lasthash(), !pingPongStatus.ok()), pingPongReply.height()};
}

/**
* Function called to initiate blockchain sync with a peer, using ping pong method
* Block headers are divided into batches and compared with the peer's remote branch
* @param peerAddress is an ipv4 or ipv6 address of the node to sync headers with
* @returns true if the blockchain could be resolved on both ends
*/
bool xcoin::Node::AttemptBlockchainSync(const std::string &peerAddress, PingPongStatus pingPongStatus,
                                        int remoteChainHeight) {
    spdlog::debug("Will attempt to sync headers with " + peerAddress);
    switch (pingPongStatus) {
        case Synced:
            spdlog::warn("Synced");
            return true;
        case ConnErr:
            spdlog::warn("Conn err");
            return false;
        case HashDiff : {
            spdlog::warn("Hash diff");
            std::vector<Block> blockVector = this->blockchain.toBlocks();
            std::reverse(blockVector.begin(), blockVector.end());
            if (SYNC_BATCHING_ENABLED){
                // TODO: Enable block batching for large blockchains
                for (size_t i = 0; i < blockVector.size(); i += 200) {
                    auto first = blockVector.begin() + i;
                    auto last = blockVector.begin() + std::min(blockVector.size(), i + 200);
                    std::vector<Block> blockBatch(first, last);
                    ::grpc::ClientContext headerFirstSyncContext;
                    xcoin::interchange::GetHeaders headerFirstSyncRequest;
                    headerFirstSyncRequest.set_version(XNODE_VERSION_INITIAL);
                    headerFirstSyncRequest.set_hashcount(last - first);
                    if (i + 200 < blockVector.size())
                        headerFirstSyncRequest.set_stophash("0");
                    else headerFirstSyncRequest.set_stophash(blockBatch.back().headerHash);
                    for (Block block: blockBatch) {
                        std::string *headerHash = headerFirstSyncRequest.add_blockheaderhashes();
                        headerHash = &block.headerHash;
                    }
                    xcoin::interchange::Headers headerFirstSyncReply;
                    ::grpc::Status headerFirstSyncStatus = this->peers[peerAddress].syncStub->HeaderFirstSync(
                            &headerFirstSyncContext, headerFirstSyncRequest, &headerFirstSyncReply);
                    if (headerFirstSyncStatus.ok()) {
                        // TODO: Handle reply
                        break;
                    } else return false;
                }
            }else{
                std::vector<std::string> hashVector = this->blockchain.toHeaderHashes();
                ::grpc::ClientContext headerFirstSyncContext;
                xcoin::interchange::GetHeaders headerFirstSyncRequest;
                xcoin::interchange::Headers headerFirstSyncReply;
                headerFirstSyncRequest.set_version(XNODE_VERSION_INITIAL);
                headerFirstSyncRequest.set_hashcount(blockVector.size());
                headerFirstSyncRequest.set_stophash("0");
                for (std::string hash: hashVector){
                    std::string *headerHash = headerFirstSyncRequest.add_blockheaderhashes();
                    headerHash = &hash;
                }
                ::grpc::Status headerFirstSyncStatus = this->peers[peerAddress].syncStub->HeaderFirstSync(
                        &headerFirstSyncContext, headerFirstSyncRequest, &headerFirstSyncReply);
                if (headerFirstSyncStatus.ok()) {
                    auto res = headerFirstSyncReply.headers();
                    std::reverse(res.begin(), res.end());
                    for (int i = 0; i < res.size(); i++){
                        if (res[i].blockheaderhash() == hashVector[i]){
                            ::grpc::ClientContext getBlockchainFromHeightContext;
                            xcoin::interchange::GetBlockchainFromHeightRequest getBlockchainFromHeightRequest;
                            xcoin::interchange::Blockchain getBlockchainFromHeightReply;
                            getBlockchainFromHeightRequest.set_stophash("0");
                            getBlockchainFromHeightRequest.set_startheight(res.size()-i);
                            ::grpc::Status getBlockchainFromHeightStatus = this->peers[peerAddress].syncStub->GetBlockchainFromHeight(
                                    &getBlockchainFromHeightContext, getBlockchainFromHeightRequest, &getBlockchainFromHeightReply);
                            if (getBlockchainFromHeightStatus.ok()){
                                Blockchain newBlockchain = Blockchain();
                                std::vector<Block> newBlocks = xcoin::interface::decodeChain(getBlockchainFromHeightReply);
                                for (Block block: newBlocks){
                                    newBlockchain.appendBlock(block);
                                }
                                this->blockchain.replaceChain(newBlockchain);
                                this->saveDataOnDisk();
                                // TODO: Decide which branch is better and just rewrite the whole thing eventually
                                return true;
                            }else return false;
                            break;
                        }
                    }
                } else return false;
            }
        }
        case HeightDiff: {
            spdlog::warn("Height diff");
            int n = this->blockchain.length;
            if (n < 0){
                return false; // Other peer must initiate sync from pingpong
            }
            std::vector<Block> blockVector = this->blockchain.toBlocks();
            std::reverse(blockVector.begin(), blockVector.end());
            ::grpc::ClientContext getBlockchainFromHeightContext;
            xcoin::interchange::GetBlockchainFromHeightRequest getBlockchainFromHeightRequest;
            xcoin::interchange::Blockchain getBlockchainFromHeightReply;
            getBlockchainFromHeightRequest.set_stophash("0");
            getBlockchainFromHeightRequest.set_startheight(n);
            ::grpc::Status getBlockchainFromHeightStatus = this->peers[peerAddress].syncStub->GetBlockchainFromHeight(
                    &getBlockchainFromHeightContext, getBlockchainFromHeightRequest, &getBlockchainFromHeightReply);

            if (getBlockchainFromHeightStatus.ok()){
                for (xcoin::interchange::Block pblock: getBlockchainFromHeightReply.blocks()){
                    Block block = xcoin::interface::decodeBlock(pblock);
                    this->blockchain.appendBlock(block);
                }
                return true;
            }else return false;
        }
    }
    return true;
}

/**
* Function called to process incoming peer data
* If the peer is known, resolve data conflicts if any, otherwise try to connect and add to known peers
* @param remotePeer the incoming peer data
* @param peerStub the control stub of the remote peer to follow up with other requests if necessary
*/
bool xcoin::Node::handleIncomingPeerData(const xcoin::interchange::DNSEntry &remotePeer) {
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

xcoin::Node::PingPongStatus
xcoin::Node::pingPongStatusForProps(int chainHeight1, int chainHeight2, const std::string& lastHash1, const std::string& lastHash2,
                                    bool isErrored) {
    if(isErrored)
        return xcoin::Node::PingPongStatus::ConnErr;
    if (chainHeight1 == chainHeight2){
        if (lastHash1 == lastHash2)
            return xcoin::Node::PingPongStatus::Synced;
        else return xcoin::Node::PingPongStatus::HashDiff;
    }else return xcoin::Node::PingPongStatus::HeightDiff;
}

void xcoin::Node::setSdkInstance(XNodeSDK *newSdkInstance) {
    this->sdkInstance = newSdkInstance;
}

XNodeSDK *xcoin::Node::getSdkInstance() const {
    return sdkInstance;
}
