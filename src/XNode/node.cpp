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
    std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
    spdlog::info("Server listening on " + server_address);
    for (const std::string& peer : dnsSeedPeers)
        this->AttemptPeerConnection(peer);
    server->Wait();
}

::grpc::Status XNode::Node::Ping(::grpc::ServerContext *context, const ::xcoin::interchange::PingHandshake *request,
                                 ::xcoin::interchange::PingHandshake *response) {
    spdlog::info("Ping received from " + context->peer());
    response->set_data(request->data());
    return xcoin::interchange::XNodeControl::Service::Ping(context, request, response);
}

::grpc::Status
XNode::Node::DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request,
                             ::xcoin::interchange::DNSHandshake *response) {
    for (auto const& x : this->peers){
        xcoin::interchange::DNSEntry *entry = response->add_entries();
        entry->set_ipport(x.first);
        entry->set_publickey(x.second.publicAddr);
    }
    return xcoin::interchange::XNodeControl::Service::DNSSyncPeerList(context, request, response);
}

void XNode::Node::AttemptPeerConnection(const std::string& peerAddress) {
    spdlog::info("Will attempt to connect to new peer " + peerAddress);
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(peerAddress, grpc::InsecureChannelCredentials());
    std::unique_ptr<xcoin::interchange::XNodeControl::Stub> stub = xcoin::interchange::XNodeControl::NewStub(channel);
    ::grpc::ClientContext context;
    xcoin::interchange::PingHandshake request;
    xcoin::interchange::PingHandshake reply;
    request.set_data("Hello!");
    ::grpc::Status status = stub->Ping(&context,request, &reply);
    if (status.ok()){
        spdlog::info("Successfully established connection with  " + peerAddress);
        this->peers[peerAddress] = XNodeClientData("<unknown>");
    }else{
        spdlog::warn("Connection with peer " + peerAddress + " failed");
    }
}
