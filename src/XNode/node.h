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
#include <drogon/WebSocketClient.h>
#include <drogon/drogon.h>

/***
 * node is the main class for Networking part of XCoin.
 * It Implements the basic functions for networking.
 */
namespace XNode{
    class node {
    public:
        node(const std::string &ip, int port);
        node(const std::string &ip, int port, bool isUsingWebSocketController, bool isWebSocketServer);

        static std::map<std::string, std::string>* name2ip;
        Blockchain blockchain;

        ~node()=default;

        void start();
        void stop();
        void setupWebSocketClient();
        std::string giveIp(std::string name);
        void addNode(std::string name, std::string ip);
        std::map<std::string, std::string> shareListNode();
    private:
        std::string ip;
        int port;
        bool isUsingWebSocketController;
        bool isWebSocketServer;



    };
}



#endif //XCOIN_XNODE_H
