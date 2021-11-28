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

        std::map<std::string, std::string> name2ip;  //problem when we put it static, to fix later
        std::string DNSseedIP = ""; //a Node knows by default the adress of the DNS seed
        Blockchain blockchain;

        ~node()=default;

        void start();
        void stop();
        void setupWebSocketClient();
        std::string giveIp(std::string name);
        void addNode(std::string name, std::string ip);
        std::map<std::string, std::string> shareListNode();
        void sendNew(std::string ip, std::string new_name, std::string new_ip);
        int NBnodes();
       std:: pair<std::string, std::string> connect(std::string name, std::string ip);
    private:
        std::string name = ""; //To put into the constructor
        std::string ip;
        int port;
        bool isUsingWebSocketController;
        bool isWebSocketServer;



    };
}



#endif //XCOIN_XNODE_H
