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
#include "archive.h"
#include "XNodeSDK.h"
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
    /// Class that contains locally resolved information about a peer
    class XNodeClient{
    public:
        XNodeClient()= default;;
        explicit XNodeClient(const std::shared_ptr<::grpc::ChannelInterface>& channel) : controlStub(xcoin::interchange::XNodeControl::NewStub(channel)),
                                                                                syncStub(xcoin::interchange::XNodeSync::NewStub(channel)){};
        std::string publicKey = XNODE_PUBLICADDR_UNKNOWN;
        std::unique_ptr<xcoin::interchange::XNodeControl::Stub> controlStub;    // Stub used to issue requests to the peer's control service
        std::unique_ptr<xcoin::interchange::XNodeSync::Stub> syncStub;          // Stub used to issue requests to the peer's sync service
        bool online = false;
    };
    /// Base class that manages the local node's lifecycle
    class Node : public xcoin::interchange::XNodeControl::Service, xcoin::interchange::XNodeSync::Service{
    public:
        explicit Node();
        ~Node() override =default;
        void RunNode(const std::vector<std::string>& dnsSeedPeers);
        void Shutdown(const std::string& reason);
        void setSDK(XNodeSDK* SDK){this->sdkInstance = SDK;};
    private:
        const uint32_t XNODE_VERSION_INITIAL = static_cast<const uint32_t>(1.1);
        const std::string XNODE_PEERS_SAVE_PATH = "localpeers.xnodebackup";
        const std::string XNODE_BLOCKCHAIN_SAVE_PATH = "localchain.xnodebackup";
        ::grpc::Status DNSSyncPeerList(::grpc::ServerContext *context, const ::xcoin::interchange::DNSHandshake *request, ::xcoin::interchange::DNSHandshake *response) override;
        ::grpc::Status Ping(::grpc::ServerContext *context, const ::xcoin::interchange::PingHandshake *request, ::xcoin::interchange::PingHandshake *response) override;
        ::grpc::Status NotifyPeerChange(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request, ::xcoin::interchange::DNSEntry *response) override;
        ::grpc::Status HeaderFirstSync(::grpc::ServerContext *context, const ::xcoin::interchange::GetHeaders *request, ::xcoin::interchange::Headers* response) override;
        ::grpc::Status GetBlock(::grpc::ServerContext *context, const ::xcoin::interchange::Header *request, ::xcoin::interchange::Block *response) override;
        ::grpc::Status GetBlockchain(::grpc::ServerContext *context, const ::xcoin::interchange::DNSEntry *request, ::xcoin::interchange::Blockchain *response) override;
        bool AttemptPeerConnection(const std::string& peerAddress);
        bool AttemptHeaderSync(const std::string& peerAddress);
        bool handleIncomingPeerData(const xcoin::interchange::DNSEntry &remotePeer);
        void saveDataOnDisk();
        void loadDataFromDisk();
        std::map<std::string, XNodeClient> peers;
        std::unique_ptr<::grpc::Server> server;
        Blockchain blockchain;
        XNodeSDK* sdkInstance;
    };
}


#endif //XCOIN_XNODE_H