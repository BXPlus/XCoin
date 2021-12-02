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
#include <drogon/WebSocketClient.h>
#include <drogon/HttpAppFramework.h>
#include <drogon/WebSocketController.h>


/***
 * node is the main class for Networking part of XCoin.
 * It Implements the basic functions for networking.
 */
namespace XNode{
    struct XNodeClientData{
        XNodeClientData() : publicAddr(), wsPtr() {}
        XNodeClientData( std::string  newPublicAddr, drogon::WebSocketConnectionPtr NewWsPtr)
                : publicAddr(std::move(newPublicAddr)), wsPtr(std::move(NewWsPtr)) {}
        std::string publicAddr;
        drogon::WebSocketConnectionPtr wsPtr;
    };
    class Node : public drogon::WebSocketController<XNode::Node, false>  {
    public:
        explicit Node(int port = 4143);

        ~Node()=default;
        void start(const std::vector<std::string>& DNSS);
        void stop();
        WS_PATH_LIST_BEGIN
            WS_PATH_ADD("/hello");
        WS_PATH_LIST_END
    private:
        int port;
        std::map<std::string, XNodeClientData> peers; // IP::port as key
        Blockchain blockchain;
        std::unique_ptr<std::thread> serverThread;
        void spawnServer() const;
        virtual void handleNewMessage(const drogon::WebSocketConnectionPtr& wsPtr,
                                      std::string && message,
                                      const drogon::WebSocketMessageType &msgType) override;
        virtual void handleNewConnection(const drogon::HttpRequestPtr & reqPtr,
                                         const drogon::WebSocketConnectionPtr& wsPtr) override;
        virtual void handleConnectionClosed(const drogon::WebSocketConnectionPtr& wsPtr) override;
        void attemptBindToNodeServer(const std::string& wsUrl);
        void attemptDNSSHandshake(const drogon::WebSocketConnectionPtr& wsPtr);
        static void log(const std::string& message, const std::string& host = "local");
    };
}



#endif //XCOIN_XNODE_H