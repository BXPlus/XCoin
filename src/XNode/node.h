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
#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>


/***
 * node is the main class for Networking part of XCoin.
 * It Implements the basic functions for networking.
 */
namespace XNode{
    struct XNodeClientData{
        XNodeClientData() : publicAddr() {}
        explicit XNodeClientData( std::string  newPublicAddr)
                : publicAddr(std::move(newPublicAddr)) {}
        std::string publicAddr;
    };
class Node : public xcoin::interchange::XNodeControl::Service, xcoin::interchange::XNodeSync::Service{
    public:
        explicit Node();
        ~Node() override =default;
        void RunNode(const std::vector<std::string>& dnsSeedPeers);
        void AttemptPeerConnection(const std::string& peerAddress);
    private:
        ::grpc::Status DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request, ::xcoin::interchange::DNSHandshake *response) override;
        ::grpc::Status Ping(::grpc::ServerContext *context, const ::xcoin::interchange::PingHandshake *request, ::xcoin::interchange::PingHandshake *response) override;
        std::map<std::string, XNodeClientData> peers; // IP::port as key
        Blockchain blockchain;
    };
}



#endif //XCOIN_XNODE_H