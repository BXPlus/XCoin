//
// Created by kevin on 11/13/21.
//
#include "node.h"

XNode::Node::Node() {
    this->blockchain = Blockchain();
    this->peers = std::map<std::string, XNode::XNodeClient>();
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

    if (this->peers.count(context->peer())==0){
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(context->peer(), grpc::InsecureChannelCredentials());
        this->peers[context->peer()] = XNodeClient(channel);
    }
    response->set_data(request->data());
    return ::grpc::Status::OK;
}

::grpc::Status
XNode::Node::DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request,
                             ::xcoin::interchange::DNSHandshake *response) {
    for (const xcoin::interchange::DNSEntry& remotePeer : request->entries())
        handleIncomingPeerData(remotePeer, std::unique_ptr<xcoin::interchange::XNodeControl::Stub>());
    for (auto const& x : this->peers){
        if (x.first != context->peer()){
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
    this->handleIncomingPeerData(*request, std::unique_ptr<xcoin::interchange::XNodeControl::Stub>());
    response->CopyFrom(*request);
    return ::grpc::Status::OK;
}


bool XNode::Node::AttemptPeerConnection(const std::string& peerAddress) {
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
    if (pingStatus.ok() && pingReply.data() == pingRequest.data()){
        spdlog::info("Successfully established connection with " + peerAddress + " with ping: " + std::to_string(((float) end - start)/CLOCKS_PER_SEC) +  "s");
        xcoin::interchange::DNSHandshake dnsRequest;
        xcoin::interchange::DNSHandshake dnsReply;
        for(auto it = peers.begin(); it != peers.end(); ++it){
            if (it->first != peerAddress){
                xcoin::interchange::DNSEntry *entry = dnsRequest.add_entries();
                entry->set_ipport(it->first);
                entry->set_publickey(it->second.publicKey);
            }
        }
        ::grpc::ClientContext dnsContext;
        ::grpc::Status dnsStatus = this->peers[peerAddress].controlStub->DNSSyncPeerList(&dnsContext, dnsRequest, &dnsReply);
        spdlog::debug("Will attempt to sync DNS with " + peerAddress);
        if (dnsStatus.ok()){
            for(const xcoin::interchange::DNSEntry& remotePeer : dnsReply.entries())
                this->handleIncomingPeerData(remotePeer, std::move(this->peers[peerAddress].controlStub));

        }else spdlog::warn("DNS peer sync with " + peerAddress + " failed");
        return true;
    }else{
        spdlog::warn("Connection with peer " + peerAddress + " failed");
        this->peers.erase(peerAddress);
        return false;
    }
}

void XNode::Node::handleIncomingPeerData(const xcoin::interchange::DNSEntry &remotePeer,
                                         std::unique_ptr<xcoin::interchange::XNodeControl::Stub> peerStub) {
    if (this->peers.count(remotePeer.ipport()) != 0){
        if (this->peers[remotePeer.ipport()].publicKey != remotePeer.publickey()){
            if(this->peers[remotePeer.ipport()].publicKey == XNODE_PUBLICADDR_UNKNOWN){
                std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(remotePeer.ipport(), grpc::InsecureChannelCredentials());
                this->peers[remotePeer.ipport()] = XNodeClient(channel);
            }
            else if (remotePeer.ipport() == XNODE_PUBLICADDR_UNKNOWN) {
                ::grpc::ClientContext context;
                xcoin::interchange::DNSEntry notificationRequest;
                xcoin::interchange::DNSEntry notificationReply;
                peerStub->NotifyPeerChange(&context,notificationRequest,&notificationReply);
                spdlog::debug("Notified peer about additional details for "+remotePeer.ipport() );
            }
            else
                return; //TODO: Ask peer directly for its details
        }
    }else{
        if(!this->AttemptPeerConnection(remotePeer.ipport()))
            spdlog::warn("Could not connect with new remote peer: " + remotePeer.ipport());
    }
}