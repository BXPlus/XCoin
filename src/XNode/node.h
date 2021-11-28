//
// Created by kevin on 11/13/21.
//

#ifndef XCOIN_XNODE_H
#define XCOIN_XNODE_H

#include <functional>
#include <string>
#include <map>
#include "Blockchain.h"
#include "controllers/xnodectl.h"
#include <iostream>
#include <thread>
#include <drogon/WebSocketClient.h>
#include <drogon/HttpAppFramework.h>


/***
 * node is the main class for Networking part of XCoin.
 * It Implements the basic functions for networking.
 */
namespace XNode{
    class node {
    public:
        explicit node(int port = 4143);

        ~node()=default;
        void start(const std::vector<std::string>& DNSS);
        void stop();
    private:
        int port;
        std::map<std::string, std::string> peerAddrs;
        std::map<std::string, drogon::WebSocketClientPtr> peerSockets;
        Blockchain blockchain;
        std::unique_ptr<std::thread> serverThread;
        void spawnServer();
        void handleIncomingMessage(const std::string &message,
                                    const drogon::WebSocketClientPtr &wsClPtr,
                                    const drogon::WebSocketMessageType &wsMsType);
        void handleConnectionClosed(const drogon::WebSocketClientPtr &wsClPtr);
        void attemptBindToNodeServer(const std::string& wsUrl);
        std::map<std::string, std::string> attemptDNSSHandshake(drogon::WebSocketClientPtr wsPtr);
        std::map<std::string, std::string> attemptPublicAddrHandshake(drogon::WebSocketClientPtr wsPtr);
        static void log(const std::string& message, const std::string& host = "local");
    };
}



#endif //XCOIN_XNODE_H
