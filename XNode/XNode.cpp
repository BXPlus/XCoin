//
// Created by kevin on 11/13/21.
//

#include <drogon/drogon.h>
#include "XNode.h"

/**
 * Constructor for the XNode class, sets the ip address and port.
 * @param ip is the ip address of the node.
 * @param port is the port of the node.
 */
XNode::XNode(const std::string &ip, const int port) {
    this->ip = ip;
    this->port = port;
}

/**
 * Starts the webserver of the node.
 */
void XNode::start() {
    drogon::app().enableReusePort();
    drogon::app()
            .addListener(this->ip, this->port)
            .setDocumentRoot("../XNode/wwwroot")
            .setThreadNum(4)
            .run();
}

/**
 * Stops the webserver of the node.
 */
void XNode::stop() {
    std::cout << "Server will stop..." << std::endl;
    drogon::app().quit();
}


