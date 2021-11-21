//
// Created by kevin on 11/13/21.
//

#ifndef XCOIN_XNODE_H
#define XCOIN_XNODE_H

#include <functional>
#include <string>

/***
 * XNode is the main class for Networking part of XCoin.
 * It Implements the basic functions for networking.
 */
class XNode {
    public:
    XNode(const std::string &ip, int port);
    XNode(const std::string &ip, int port, bool isUsingWebSocketController, bool isWebSocketServer);

    ~XNode() = default;

        void start();
        void stop();
        void setupWebSocketClient();
private:
    std::string ip;
    int port;
    bool isUsingWebSocketController;
    bool isWebSocketServer;
};


#endif //XCOIN_XNODE_H
