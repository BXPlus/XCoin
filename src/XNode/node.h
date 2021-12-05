//
// Created by kevin on 11/13/21.
//

#ifndef XCOIN_XNODE_H
#define XCOIN_XNODE_H

#define XNODE_PUBLICADDR_UNKNOWN "<unknown>"

#include <functional>
#include <string>
#include <map>
#include "Blockchain.h"
#include "interface.h"
#include <iostream>
#include <thread>
#include <memory>
#include <utility>
#include <chrono>
#include <blockchain.grpc.pb.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>

namespace XNode{
    class XNodeClient{
    public:
        XNodeClient(){};
        explicit XNodeClient(const std::shared_ptr<::grpc::ChannelInterface>& channel) : controlStub(xcoin::interchange::XNodeControl::NewStub(channel)),
                                                                                syncStub(xcoin::interchange::XNodeSync::NewStub(channel)){};
        void setPublicKey(std::string newPublicKey){this->publicKey = std::move(newPublicKey);};
        void setOnline(bool newOnline){this->online = newOnline;};
        std::string publicKey = XNODE_PUBLICADDR_UNKNOWN;
        std::unique_ptr<xcoin::interchange::XNodeControl::Stub> controlStub;
        std::unique_ptr<xcoin::interchange::XNodeSync::Stub> syncStub;
        bool online = false;
    };
    class Node : public xcoin::interchange::XNodeControl::Service, xcoin::interchange::XNodeSync::Service{
    public:
        explicit Node();
        ~Node() override =default;
        void RunNode(const std::vector<std::string>& dnsSeedPeers);
        bool AttemptPeerConnection(const std::string& peerAddress);
        bool AttemptHeaderSync(const std::string& peerAddress);
    private:
        ::grpc::Status DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request, ::xcoin::interchange::DNSHandshake *response) override;
        ::grpc::Status Ping(::grpc::ServerContext *context, const ::xcoin::interchange::PingHandshake *request, ::xcoin::interchange::PingHandshake *response) override;
        ::grpc::Status NotifyPeerChange(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request, ::xcoin::interchange::DNSEntry *response) override;
        ::grpc::Status HeaderFirstSync(::grpc::ServerContext *context, const ::xcoin::interchange::GetHeaders *request, ::xcoin::interchange::Headers* response) override;
        void handleIncomingPeerData(const xcoin::interchange::DNSEntry &remotePeer);
        void handleIncomingHeaderData(const std::basic_string<char> &remoteHeader,
                                      std::unique_ptr<xcoin::interchange::XNodeSync::Stub> peerStub);
        std::map<std::string, XNodeClient> peers;
        std::unique_ptr<::grpc::Server> server;
        Blockchain blockchain;
    };
}


#endif //XCOIN_XNODE_H