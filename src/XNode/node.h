//
// Created by kevin on 11/13/21.
//

#ifndef XCOIN_XNODE_H
#define XCOIN_XNODE_H

#include <functional>
#include <string>
#include <map>
#include "Blockchain.h"
#include "interface.h"
#include <iostream>
#include <thread>
#include <memory>
#include <utility>
#include <blockchain.grpc.pb.h>
#include <grpcpp/server_builder.h>


/***
 * node is the main class for Networking part of XCoin.
 * It Implements the basic functions for networking.
 */
namespace XNode{
    struct XNodeClientData{
        XNodeClientData() : publicAddr() {}
        XNodeClientData( std::string  newPublicAddr)
                : publicAddr(std::move(newPublicAddr)) {}
        std::string publicAddr;
    };
class Node : public xcoin::interchange::DNS::Service {
    public:
        explicit Node(int port = 4143);
        ~Node()=default;
        void RunServer();
        ::grpc::Status GetPeerList(::grpc::ServerContext* context, const ::xcoin::interchange::DNSHandshake* request, ::xcoin::interchange::DNSHandshake* response) override;
    private:
        int port;
        std::map<std::string, XNodeClientData> peers; // IP::port as key
        Blockchain blockchain;
        static void log(const std::string& message, const std::string& host = "local");
    };
}



#endif //XCOIN_XNODE_H