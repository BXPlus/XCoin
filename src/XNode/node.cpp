//
// Created by kevin on 11/13/21.
//
#include "node.h"

XNode::Node::Node() {
    this->blockchain = Blockchain();
    this->peers = std::map<std::string, XNode::XNodeClient>();
}

/**
* Function called to start up a node, initiate peer-discovery & synchronisation
* @param dnsSeedPeers is a list of DNS seed node addresses to attempt initial connections
*/
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

/**
* Callback function executed by gRPC to process incoming Ping requests from peers
* Add the peer to the list of known nodes if necessary and replies with ping data
*/
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

/**
* Callback function executed by gRPC to process incoming DNS Sync requests from peers
* Handles incoming peers and replies with own known peers
*/
::grpc::Status
XNode::Node::DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request,
                             ::xcoin::interchange::DNSHandshake *response) {
    spdlog::debug("DNS sync requested by " + context->peer());
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

/**
* Callback function executed by gRPC to process incoming peer change notifications from peers
* Handles new peer data and sends back to confirm
*/
::grpc::Status
XNode::Node::NotifyPeerChange(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request,
                              ::xcoin::interchange::DNSEntry *response) {
    this->handleIncomingPeerData(*request, std::unique_ptr<xcoin::interchange::XNodeControl::Stub>());
    response->CopyFrom(*request);
    return ::grpc::Status::OK;
}

/**
* Function called to try to connect to a remote peer
* If ping request is successful, DNS sync is performed, and ping is calculated
* @param peerAddress is an ipv4 or ipv6 address of a potential remote node to connect to
* @returns true if the connection and handshake was successful
*/
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
        if (dnsStatus.ok()){
            for(const xcoin::interchange::DNSEntry& remotePeer : dnsReply.entries())
                this->handleIncomingPeerData(remotePeer, std::move(this->peers[peerAddress].controlStub));
            spdlog::info("Successfully synced DNS peers with " + peerAddress);
            return true;
        }else spdlog::warn("DNS peer sync with " + peerAddress + " failed");
        return true;
    }else{
        spdlog::warn("Connection with peer " + peerAddress + " failed");
        this->peers.erase(peerAddress);
        return false;
    }
}

/**
* Function called to process incoming peer data
* If the peer is known, resolve data conflicts if any, otherwise try to connect and add to known peers
* @param remotePeer the incoming peer data
* @param peerStub the control stub of the remote peer to follow up with other requests if necessary
*/
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