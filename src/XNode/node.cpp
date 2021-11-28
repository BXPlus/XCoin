//
// Created by kevin on 11/13/21.
//
#include "node.h"

/**
 * Constructor for the node class for using HttpControllers, sets the ip address and port.
 * @param ip is the ip address of the node.
 * @param port is the port of the node.
 */
XNode::node::node(const std::string &ip, int port) {
    this->ip = ip;
    this->port = port;
    this->isWebSocketServer = false;
    this->isUsingWebSocketController = false;
    //TODO : Fetch Blockchain from cache (file).
    this->blockchain = Blockchain();
    this->name2ip = std::map<std::string, std::string>();


    /*
     *
     * Request the list of Nodes of the DNS seed
     *
     */
    std::map<std::string, std::string> received ;  //the received dictionary

    name2ip = received;
    this->name2ip["self"] = ip;



}

/**
 * Overload constructor for the node class for using WebSocket controllers, sets the ip address, port.
 * @param ip is the ip address of the node.
 * @param port is the port of the node.
 * @param isWebSocketServer is a boolean value that determines if the node is a websocket server.
 */
XNode::node::node(const std::string &ip, const int port, const bool isUsingWebSocketController, const bool isWebSocketServer) {
    this->ip = ip;
    this->port = port;
    this->isWebSocketServer = isWebSocketServer;
    this->isUsingWebSocketController = isUsingWebSocketController;
}

/**
 * Starts the webserver of the node.
 */
void XNode::node::start() {
    //drogon::app().enableReusePort();
    if (!isUsingWebSocketController || isWebSocketServer)
        drogon::app()
            .addListener(this->ip, this->port)
            .setDocumentRoot("../src/node/wwwroot")
            .setThreadNum(4)
            .run();
    else{
        std::string path;
        path = "/hello";

        std::string serverString;
        serverString = "ws://" + this->ip + ":" + std::to_string(this->port);
        auto wsPtr = drogon::WebSocketClient::newWebSocketClient(serverString);
        auto req = drogon::HttpRequest::newHttpRequest();
        req->setPath(path);

        wsPtr->setMessageHandler([](const std::string &message,
                                    const drogon::WebSocketClientPtr &,
                                    const drogon::WebSocketMessageType &type) {

            std::cout << "new message: " << message;
        });

        wsPtr->setConnectionClosedHandler([](const drogon::WebSocketClientPtr &) {
            std::cout << "WebSocket connection closed!";
        });

        std::cout << "Connecting to WebSocket at " << this->ip;
        wsPtr->connectToServer(
                req,
                [](drogon::ReqResult r,
                   const drogon::HttpResponsePtr &,
                   const drogon::WebSocketClientPtr &wsPtr) {
                    if (r != drogon::ReqResult::Ok)
                    {
                        std::cout << "Failed to establish WebSocket connection!";
                        wsPtr->stop();
                        return;
                    }
                    std::cout << "WebSocket connected!";
                    wsPtr->getConnection()->send("hello!");
                });
        drogon::app().run();

    }
}

/**
 * Stops the webserver of the node.
 */
void XNode::node::stop() {
    std::cout << "Server will stop..." << std::endl;
    drogon::app().quit();
}



/**
 * This function sets up the WebSocketClient for the node.
 */
void XNode::node::setupWebSocketClient() {
    const std::string wsUrl = "ws://" + this->ip + ":" + std::to_string(this->port);

    // Example of a path to which the server sends you back the message you sent.
    const std::string path("/hello");

    // Establish a WebSocket connection to the server.
    drogon::WebSocketClientPtr wsPtr = drogon::WebSocketClient::newWebSocketClient(wsUrl);
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

    std::cout << "Connecting to WebSocket at " << wsUrl << std::endl;

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
                //wsPtr->getConnection()->setPingMessage("", 2s); //Sends a message every 2 seconds.

                // Send hello to the server.
                wsPtr->getConnection()->send("hello!");
            });
}


std::string XNode::node::giveIp(std::string name){
    std::string ret = name2ip[name];
    if (ret==""){
        return "None";
    }
    return ret;

}

void XNode::node::addNode(std::string name, std::string ip) {

    if (name2ip.find("name") != name2ip.end()){
        return;
    }
    name2ip[name] = ip;
    for (std::map<std::string, std::string>::iterator i = name2ip.begin(); i != name2ip.end(); ++i){
        sendNew(i->second, name, ip);
    }
}

std::map<std::string, std::string> XNode::node::shareListNode() {
    return name2ip;
}

int XNode::node::NBnodes() {

    return name2ip.size();
}

std::pair<std::string, std::string> XNode::node::connect(std::string name, std::string ip) {
    addNode(name, ip);
    return std::pair(this->name, this->ip);
}
void sendNew(std::string ip, std::string new_name, std::string new_ip){
    /*
     * To define
     *
     * Send to 'ip' the 'new_name' and 'new_ip' which is new for him
     */
}
/*
Blockchain node::node::getBlockchain() {
    return node::blockchain;
}
*/
