//
// Created by kevin on 11/13/21.
//

#ifndef XCOIN_XNODE_H
#define XCOIN_XNODE_H

#include <functional>
#include <string>
#include <map>
#include "../XBlockchain/Blockchain.h"

/***
 * XNode is the main class for Networking part of XCoin.
 * It Implements the basic functions for networking.
 */
namespace XNode{
    class XNode {
    public:
        XNode(const std::string &ip, int port);
        XNode(const std::string &ip, int port, bool isUsingWebSocketController, bool isWebSocketServer);

        static std::map<std::string, std::string>* name2ip;
        static Blockchain getBlockchain();

        ~XNode()=default;

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
        static Blockchain blockchain;


    };
}



#endif //XCOIN_XNODE_H
