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
#include <drogon/HttpAppFramework.h>


/***
 * node is the main class for Networking part of XCoin.
 * It Implements the basic functions for networking.
 */
namespace XNode{
    class node {
    public:
        node(const std::string &ip, int port);
        node(const std::string &ip, int port, bool isUsingWebSocketController, bool isWebSocketServer);

        std::map<std::string, std::string> name2ip;  //problem when we put it static
        Blockchain blockchain;

        ~node()=default;

        void start();
        void stop();
        void setupWebSocketClient();
        std::string giveIp(std::string name);
        void addNode(std::string name, std::string ip);
        std::map<std::string, std::string> shareListNode();
        int NBnodes();
    private:
        std::string ip;
        int port;
        bool isUsingWebSocketController;
        bool isWebSocketServer;



    };
}



#endif //XCOIN_XNODE_H
