//
// Created by kevin on 11/13/21.
//
#include "node.h"

XNode::Node::Node() {
    this->blockchain = Blockchain();
    this->peers = std::map<std::string, XNodeClientData>();
}

void XNode::Node::RunNode(const std::vector<std::string>& dnsSeedPeers) {
    std::string server_address("0.0.0.0:50051");
    ::grpc::EnableDefaultHealthCheckService(true);
    ::grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, ::grpc::InsecureServerCredentials());
    builder.RegisterService(static_cast<xcoin::interchange::XNodeControl::Service*>(this));
    this->server = builder.BuildAndStart();
    spdlog::info("Server listening on " + server_address);
    bool couldPerformHandshakeWithDNSS = false;
    for (const std::string& peer : dnsSeedPeers)
        couldPerformHandshakeWithDNSS |= this->AttemptPeerConnection(peer);
    if(!couldPerformHandshakeWithDNSS && !dnsSeedPeers.empty()){
        spdlog::error("Could not establish connection with any DNSS, node will shut down...");
        server->Shutdown();
        exit(EXIT_SUCCESS);
    }
    server->Wait();
}

::grpc::Status XNode::Node::Ping(::grpc::ServerContext *context, const ::xcoin::interchange::PingHandshake *request,
                                 ::xcoin::interchange::PingHandshake *response) {
    spdlog::debug("Ping received from " + context->peer());
    if (this->peers.count(context->peer())==0)
        this->peers[context->peer()] = XNodeClientData(XNODE_PUBLICADDR_UNKNOWN);
    response->set_data(request->data());
    return ::grpc::Status::OK;
}

::grpc::Status
XNode::Node::DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request,
                             ::xcoin::interchange::DNSHandshake *response) {
    for (const xcoin::interchange::DNSEntry& remotePeer : request->entries())
        handleIncomingPeerData(remotePeer);
    for (auto const& x : this->peers){
        xcoin::interchange::DNSEntry *entry = response->add_entries();
        entry->set_ipport(x.first);
        entry->set_publickey(x.second.publicAddr);
    }
    return ::grpc::Status::OK;
}

bool XNode::Node::AttemptPeerConnection(const std::string& peerAddress) {
    spdlog::debug("Will attempt to connect to new peer " + peerAddress);
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(peerAddress, grpc::InsecureChannelCredentials());
    std::unique_ptr<xcoin::interchange::XNodeControl::Stub> stub = xcoin::interchange::XNodeControl::NewStub(channel);
    ::grpc::ClientContext context;
    xcoin::interchange::PingHandshake pingRequest;
    xcoin::interchange::PingHandshake pingReply;
    pingRequest.set_data("Hello!");
    clock_t start = clock();
    ::grpc::Status pingStatus = stub->Ping(&context, pingRequest, &pingReply);
    clock_t end = clock();
    if (pingStatus.ok() && pingReply.data() == pingRequest.data()){
        spdlog::info("Successfully established connection with " + peerAddress + " with ping: " + std::to_string(((float) end - start)/CLOCKS_PER_SEC) +  "s");
        this->peers[peerAddress] = XNodeClientData(XNODE_PUBLICADDR_UNKNOWN);
        xcoin::interchange::DNSHandshake dnsRequest;
        xcoin::interchange::DNSHandshake dnsReply;
        for(std::pair<const std::basic_string<char>, XNodeClientData> client : this->peers){
            xcoin::interchange::DNSEntry *entry = dnsRequest.add_entries();
            entry->set_ipport(client.first);
            entry->set_publickey(client.second.publicAddr);
        }
        ::grpc::Status dnsStatus = stub->DNSSyncPeerList(&context, dnsRequest, &dnsReply);
        if (dnsStatus.ok()){
            for(const xcoin::interchange::DNSEntry& remotePeer : dnsReply.entries())
                this->handleIncomingPeerData(remotePeer);
        }else spdlog::warn("DNS peer sync with " + peerAddress + " failed");
        return true;
    }else{
        spdlog::warn("Connection with peer " + peerAddress + " failed");
        return false;
    }
}

void XNode::Node::handleIncomingPeerData(const xcoin::interchange::DNSEntry& remotePeer) {
    if (this->peers.count(remotePeer.ipport()) != 0){
        if (this->peers[remotePeer.ipport()].publicAddr != remotePeer.publickey()){
            if(this->peers[remotePeer.ipport()].publicAddr == XNODE_PUBLICADDR_UNKNOWN)
                this->peers[remotePeer.ipport()] = XNodeClientData(remotePeer.publickey());
            else if (remotePeer.ipport() == XNODE_PUBLICADDR_UNKNOWN)
                return; //TODO: Special message to update client data
            else
                return; //TODO: Ask peer directly for its details
        }
    }else{
        if(!this->AttemptPeerConnection(remotePeer.ipport()))
            spdlog::warn("Could not connect with new remote peer: " + remotePeer.ipport());
    }
}
