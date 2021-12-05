//
// Created by kevin on 11/13/21.
//
#include "node.h"

XNode::Node::Node() {
    this->blockchain = Blockchain();
    this->peers = std::map<std::string, XNode::XNodeClient>();
}

void XNode::Node::RunNode(const std::vector<std::string> &dnsSeedPeers) {
    std::string server_address("0.0.0.0:50051");
    ::grpc::EnableDefaultHealthCheckService(true);
    ::grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, ::grpc::InsecureServerCredentials());
    builder.RegisterService(static_cast<xcoin::interchange::XNodeControl::Service *>(this));
    this->server = builder.BuildAndStart();
    spdlog::info("Server listening on " + server_address);
    bool couldPerformHandshakeWithDNSS = false;
    for (const std::string &peer: dnsSeedPeers)
        couldPerformHandshakeWithDNSS |= this->AttemptPeerConnection(peer);
    if (!couldPerformHandshakeWithDNSS && !dnsSeedPeers.empty()) {
        spdlog::error("Could not establish connection with any DNSS, node will shut down...");
        server->Shutdown();
        exit(EXIT_SUCCESS);
    }
    server->Wait();
}

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

::grpc::Status
XNode::Node::DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request,
                             ::xcoin::interchange::DNSHandshake *response) {
    spdlog::debug("DNS sync requested by " + context->peer());
    for (const xcoin::interchange::DNSEntry &remotePeer: request->entries())
        handleIncomingPeerData(remotePeer);
    for (const std::pair<const std::basic_string<char>, XNodeClient> &x: this->peers) {
        if (x.first != context->peer()) {
            xcoin::interchange::DNSEntry *entry = response->add_entries();
            entry->set_ipport(x.first);
            entry->set_publickey(x.second.publicKey);
        }
    }
    return ::grpc::Status::OK;
}

::grpc::Status
XNode::Node::NotifyPeerChange(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request,
                              ::xcoin::interchange::DNSEntry *response) {
    this->handleIncomingPeerData(*request);
    response->CopyFrom(*request);
    return ::grpc::Status::OK;
}

::grpc::Status
XNode::Node::HeaderFirstSync(::grpc::ServerContext *context, const ::xcoin::interchange::GetHeaders *request,
                             ::xcoin::interchange::Headers *response) {
    spdlog::debug("Header first sync requested by " + context->peer());
    ::grpc::ClientContext getHeaderContext;
    xcoin::interchange::Header getHeaderRequest;
    xcoin::interchange::Block getHeaderResponse;

    // TODO: Delete this later
    ::grpc::ClientContext getBlockChainContext;
    xcoin::interchange::DNSEntry getBlockChainRequest;
    xcoin::interchange::Blockchain getBlockChainResponse;

    for (int i = 1; i < request->blockheaderhashes_size(); i++) {
        if (request->blockheaderhashes(i) != this->blockchain.toBlocks()[i].headerHash) {
            getHeaderRequest.set_previousblockheaderhash(request->blockheaderhashes(i - 1));
            peers[context->peer()].syncStub->GetBlock(
                    &getHeaderContext,
                    getHeaderRequest,
                    &getHeaderResponse);
            // TODO: Use the response to construct the new blockchain, right now we will just import the blockchain from the peer and check which one is valid.
            getBlockChainRequest.set_ipport(context->peer()); // Not even useful to do this.
            peers[context->peer()].syncStub->GetBlockchain(
                    &getBlockChainContext,
                    getBlockChainRequest,
                    &getBlockChainResponse);
            Blockchain peerBlockchain = Blockchain();
            for (const xcoin::interchange::Block &block: getBlockChainResponse.blocks())
                peerBlockchain.appendBlock((Block((int) block.index(),
                                                  block.hash(),
                                                  block.previoushash(),
                                                  block.headerhash(),
                                                  block.previousheaderhash(),
                                                  block.timestamp(),
                                                  block.data(),
                                                  (int) block.difficulty(),
                                                  (int) block.minterbalance(),
                                                  block.minteraddress())));
            this->blockchain.replaceChain(peerBlockchain);
            break;

        }
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
    for (const Block &block: this->blockchain.toBlocks()) {
        if (block.previousHeaderHash == request->previousblockheaderhash() &&
            block.merkle_root_hash == request->merkleroothash() &&
            block.timestamp == request->time()) {
            xcoin::interchange::Block *blockResponse = response->New();
            blockResponse->set_index(block.index);
            blockResponse->set_hash(block.hash);
            blockResponse->set_previoushash(block.previousHash);
            blockResponse->set_headerhash(block.headerHash);
            blockResponse->set_previousheaderhash(block.previousHeaderHash);
            blockResponse->set_timestamp(block.timestamp);
            blockResponse->set_data(block.data);
            blockResponse->set_difficulty(block.difficulty);
            blockResponse->set_nonce(block.nonce);
            blockResponse->set_minterbalance(block.minterBalance);
            blockResponse->set_minteraddress(block.minterAddress);
            blockResponse->set_merkle_root_hash(block.merkle_root_hash);
            return ::grpc::Status::OK;
        }
    }
    return ::grpc::Status::CANCELLED;
}

::grpc::Status
XNode::Node::GetBlockchain(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request,
                           ::xcoin::interchange::Blockchain *response) {
    xcoin::interchange::Blockchain *blockchainResponse = response->New();
    for (const Block &block: this->blockchain.toBlocks()) {
        xcoin::interchange::Block *blockResponse = blockchainResponse->add_blocks();
        blockResponse->set_index(block.index);
        blockResponse->set_hash(block.hash);
        blockResponse->set_previoushash(block.previousHash);
        blockResponse->set_headerhash(block.headerHash);
        blockResponse->set_previousheaderhash(block.previousHeaderHash);
        blockResponse->set_timestamp(block.timestamp);
        blockResponse->set_data(block.data);
        blockResponse->set_difficulty(block.difficulty);
        blockResponse->set_nonce(block.nonce);
        blockResponse->set_minterbalance(block.minterBalance);
        blockResponse->set_minteraddress(block.minterAddress);
        blockResponse->set_merkle_root_hash(block.merkle_root_hash);
    }
    return ::grpc::Status::OK;
}

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
        for (std::pair<const std::basic_string<char>, XNodeClient> &peer: peers) {
            if (peer.first != peerAddress) {
                xcoin::interchange::DNSEntry *entry = dnsRequest.add_entries();
                entry->set_ipport(peer.first);
                entry->set_publickey(peer.second.publicKey);
            }
        }
        ::grpc::ClientContext dnsContext;
        ::grpc::Status dnsStatus = this->peers[peerAddress].controlStub->DNSSyncPeerList(&dnsContext, dnsRequest,
                                                                                         &dnsReply);
        if (dnsStatus.ok()) {
            for (const xcoin::interchange::DNSEntry &remotePeer: dnsReply.entries())
                this->handleIncomingPeerData(remotePeer);
            spdlog::info("Successfully synced DNS peers with " + peerAddress);
            return true;
        } else spdlog::warn("DNS peer sync with " + peerAddress + " failed");
        return AttemptHeaderSync(peerAddress);
    } else {
        spdlog::warn("Connection with peer " + peerAddress + " failed");
        this->peers.erase(peerAddress);
        return false;
    }
}

bool XNode::Node::AttemptHeaderSync(const std::string &peerAddress) {
    spdlog::debug("Will attempt to proceed a header sync to the peer " + peerAddress);
    ::grpc::ClientContext headerFirstSyncContext;
    xcoin::interchange::GetHeaders headerFirstSyncRequest;
    xcoin::interchange::Headers headerFirstSyncReply;
    ::grpc::Status headerFirstSyncStatus = this->peers[peerAddress].syncStub->HeaderFirstSync(
            &headerFirstSyncContext, headerFirstSyncRequest, &headerFirstSyncReply);
    // TODO: Delete this later
    ::grpc::ClientContext getBlockChainContext;
    xcoin::interchange::DNSEntry getBlockChainRequest;
    xcoin::interchange::Blockchain getBlockChainResponse;
    if (headerFirstSyncStatus.ok()) {
        for (int i = 1; i < headerFirstSyncRequest.blockheaderhashes_size(); i++) {
            if (headerFirstSyncRequest.blockheaderhashes(i) != this->blockchain.toBlocks()[i].headerHash) {
//                getHeaderRequest.set_previousblockheaderhash(headerFirstSyncRequest.blockheaderhashes(i-1));
//                peers[context->peer()].syncStub->GetBlock(
//                        &getHeaderContext,
//                        getHeaderRequest,
//                        &getHeaderResponse);
                // TODO: Use the response to construct the new blockchain, right now we will just import the blockchain from the peer and check which one is valid.
                getBlockChainRequest.set_ipport(headerFirstSyncContext.peer()); // Not even useful to do this.
                peers[headerFirstSyncContext.peer()].syncStub->GetBlockchain(
                        &getBlockChainContext,
                        getBlockChainRequest,
                        &getBlockChainResponse);
                Blockchain peerBlockchain = Blockchain();
                for (const xcoin::interchange::Block &block: getBlockChainResponse.blocks())
                    peerBlockchain.appendBlock((Block((int) block.index(),
                                                      block.hash(),
                                                      block.previoushash(),
                                                      block.headerhash(),
                                                      block.previousheaderhash(),
                                                      block.timestamp(),
                                                      block.data(),
                                                      (int) block.difficulty(),
                                                      (int) block.minterbalance(),
                                                      block.minteraddress())));
                this->blockchain.replaceChain(peerBlockchain);
                break;

            }
        }
        spdlog::info("Successfully synced headers with " + peerAddress);
        return true;
    }
    return false;
}


void XNode::Node::handleIncomingPeerData(const xcoin::interchange::DNSEntry &remotePeer) {
    if (this->peers.count(remotePeer.ipport()) != 0) {
        if (this->peers[remotePeer.ipport()].publicKey != remotePeer.publickey()) {
            if (this->peers[remotePeer.ipport()].publicKey == XNODE_PUBLICADDR_UNKNOWN) {
                std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(remotePeer.ipport(),
                                                                             grpc::InsecureChannelCredentials());
                this->peers[remotePeer.ipport()] = XNodeClient(channel);
            } else if (remotePeer.ipport() == XNODE_PUBLICADDR_UNKNOWN) {
                ::grpc::ClientContext context;
                xcoin::interchange::DNSEntry notificationRequest;
                xcoin::interchange::DNSEntry notificationReply;
                peers[remotePeer.ipport()].controlStub->NotifyPeerChange(&context, notificationRequest,
                                                                         &notificationReply);
                spdlog::debug("Notified peer about additional details for " + remotePeer.ipport());
            } else
                return; //TODO: Ask peer directly for its details
        }
    } else {
        if (!this->AttemptPeerConnection(remotePeer.ipport()))
            spdlog::warn("Could not connect with new remote peer: " + remotePeer.ipport());
    }
}

void XNode::Node::handleIncomingHeaderData(const xcoin::interchange::GetHeaders &request,
                                           const ::grpc::ClientContext &context,
                                           std::unique_ptr<xcoin::interchange::XNodeSync::Stub> peerStub) {

}




