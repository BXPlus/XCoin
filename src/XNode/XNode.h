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
    XNode(const std::string &ip, const int port);

    ~XNode() = default;

        void start();
        void stop();
        //void setupWebSocket();
private:
    std::string ip;
    int port;
};


#endif //XCOIN_XNODE_H
