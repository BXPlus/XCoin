//
// Created by kevin on 11/13/21.
//

#include <drogon/drogon.h>
#include "XNode.h"

XNode::XNode(const std::string &ip, const int port) {
    this->ip = ip;
    this->port = port;
}

void XNode::start() {
    drogon::app().enableReusePort();
    drogon::app().addListener(this->ip,this->port).setThreadNum(4).run();
}

void XNode::stop() {
    std::cout << "Server will stop..." << std::endl;
    drogon::app().quit();
}


