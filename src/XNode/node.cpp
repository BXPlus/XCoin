//
// Created by kevin on 11/13/21.
//
#include "node.h"

/**
 * Constructor for the node class. Starts up a node on the XCoin network.
 * @param DNSS is a list of potential DNS seeds to query on startup
 * @param port is the port to use, 4143 by default
 */

XNode::Node::Node(const int port) {
    this->port = port;
    this->blockchain = Blockchain();
    this->peers = std::map<std::string, XNodeClientData>();
}

void XNode::Node::log(const std::string& message, const std::string& host) {
    std::cout << host + "    " + message << std::endl;
}

::grpc::Status
XNode::Node::GetPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request,
                         ::xcoin::interchange::DNSHandshake *response) {
    for (auto const& x : this->peers){
        xcoin::interchange::DNSEntry *entry = response->add_entries();
        entry->set_ipport(x.first);
        entry->set_publickey(x.second.publicAddr);
    }
    return Service::GetPeerList(context, request, response);
}

void XNode::Node::RunServer() {
    std::string server_address("0.0.0.0:50051");
    ::grpc::EnableDefaultHealthCheckService(true);
    ::grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, ::grpc::InsecureServerCredentials());
    builder.RegisterService(this);
    std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}
