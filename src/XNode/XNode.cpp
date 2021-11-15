//
// Created by kevin on 11/13/21.
//

#include <drogon/drogon.h>
#include "XNode.h"
#include "controllers/xnodectl.h"
#include <iostream>
#include <drogon/WebSocketClient.h>

/**
 * Constructor for the XNode class for using HttpControllers, sets the ip address and port.
 * @param ip is the ip address of the node.
 * @param port is the port of the node.
 */
XNode::XNode(const std::string &ip, int port) {
    this->ip = ip;
    this->port = port;
    this->isWebSocketServer = false;
    this->isUsingWebSocketController = false;
}

/**
 * Overload constructor for the XNode class for using WebSocket controllers, sets the ip address, port.
 * @param ip is the ip address of the node.
 * @param port is the port of the node.
 * @param isWebSocketServer is a boolean value that determines if the node is a websocket server.
 */
XNode::XNode(const std::string &ip, const int port, const bool isUsingWebSocketController, const bool isWebSocketServer) {
    this->ip = ip;
    this->port = port;
    this->isWebSocketServer = isWebSocketServer;
    this->isUsingWebSocketController = isUsingWebSocketController;
}

/**
 * Starts the webserver of the node.
 */
void XNode::start() {
    drogon::app().enableReusePort();
    if (!isUsingWebSocketController || isWebSocketServer)
        drogon::app()
            .addListener(this->ip, this->port)
            .setDocumentRoot("../src/XNode/wwwroot")
            .setThreadNum(4)
            .run();
    else{
        setupWebSocketClient();
        // drogon::app().getLoop()->runAfter(15, [this]() { stop(); }); Stops the server after 15 seconds.
        drogon::app().setThreadNum(4).run();

    }
}

/**
 * Stops the webserver of the node.
 */
void XNode::stop() {
    std::cout << "Server will stop..." << std::endl;
    drogon::app().quit();
}



/**
 * This function sets up the WebSocketClient for the node.
 */
void XNode::setupWebSocketClient() {
    const std::string wsUrl = "ws://" + this->ip + ":" + std::to_string(this->port);

    // Example of a path to which the server sends you back the message you sent.
    const std::string path("/hello");

    // Establish a WebSocket connection to the server.
    drogon::WebSocketClientPtr wsPtr = drogon::WebSocketClient::newWebSocketClient(ip);
    // Create an Http request.
    drogon::HttpRequestPtr req = drogon::HttpRequest::newHttpRequest();
    // Set up the path for the request.
    req->setPath(path);

    // Handle incoming messages from the server.
    wsPtr->setMessageHandler([](const std::string &message,
                                const drogon::WebSocketClientPtr &,
                                const drogon::WebSocketMessageType &type) {

        std::cout << "new message " << message << std::endl;

    });

    // Handle closing connection from server.
    wsPtr->setConnectionClosedHandler([](const drogon::WebSocketClientPtr &) {
        std::cout << "WebSocket connection closed!" << std::endl;
    });

    std::cout << "Connecting to WebSocket at " << ip << std::endl;

    // Connect to the WebSocket server.
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
                // wsPtr->getConnection()->setPingMessage("", 2s); Sends a message every 2 seconds.

                // Send hello to the server.
                wsPtr->getConnection()->send("hello!");
            });
}
