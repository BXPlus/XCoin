//
// Created by kevin on 11/13/21.
//

#include <drogon/drogon.h>
#include "XNode.h"
#include "controllers/xnodectl.h"
#include <iostream>
using namespace std::chrono_literals;
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

    // TODO: Issue I am facing right now is that I cannot have a websocket server and websocket client running
    //       simultaneously since drogon().app().run() blocks the main thread.
    drogon::app()
            .addListener(this->ip, this->port)
            .setDocumentRoot("../src/XNode/wwwroot")
            .setThreadNum(4)
            .run();
    // setupWebSocket(); We ignore this for now as we first implement a HttpController.
}

/**
 * Stops the webserver of the node.
 */
void XNode::stop() {
    std::cout << "Server will stop..." << std::endl;
    drogon::app().quit();
}

/**
 * This function aims to connect to a websocket server.
 * Code imported from the documentation of drogon.
 * Do not use it as we first implement a HttpController.
 */
/*void XNode::setupWebSocket() {
    std::string server;
    std::string path;
    drogon::optional<uint16_t> port2;
    // Connect to a public echo server
    server = "0.0.0.0";
    port2 = 80;
    path = "/hello";

    std::string serverString;
    if (port2.value_or(0) != 0)
        serverString = server + ":" + std::to_string(port2.value());
    else
        serverString = server;
    auto wsPtr = drogon::WebSocketClient::newWebSocketClient(serverString);
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setPath(path);

    wsPtr->setMessageHandler([](const std::string &message,
                                const drogon::WebSocketClientPtr &,
                                const drogon::WebSocketMessageType &type) {
        std::string messageType = "Unknown";
        if (type == drogon::WebSocketMessageType::Text)
            messageType = "text";
        else if (type == drogon::WebSocketMessageType::Pong)
            messageType = "pong";
        else if (type == drogon::WebSocketMessageType::Ping)
            messageType = "ping";
        else if (type == drogon::WebSocketMessageType::Binary)
            messageType = "binary";
        else if (type == drogon::WebSocketMessageType::Close)
            messageType = "Close";

        std::cout << "new message (" << messageType << "): " << message << std::endl;
    });

    wsPtr->setConnectionClosedHandler([](const drogon::WebSocketClientPtr &) {
        std::cout << "WebSocket connection closed!" << std::endl;
    });

    std::cout << "Connecting to WebSocket at " << server << std::endl;
    wsPtr->connectToServer(
            req,
            [](drogon::ReqResult r,
               const drogon::HttpResponsePtr &,
               const drogon::WebSocketClientPtr &wsPtr) {
                if (r != drogon::ReqResult::Ok)
                {
                    std::cout << "Failed to establish WebSocket connection!" << std::endl;
                    wsPtr->stop();
                    return;
                }
                std::cout << "WebSocket connected!" << std::endl;
                wsPtr->getConnection()->setPingMessage("", 2s);
                wsPtr->getConnection()->send("hello!");
            });
}*/

