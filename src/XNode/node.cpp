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

void XNode::Node::start(const std::vector<std::string>& DNSS) {
    //TODO : Fetch Blockchain from cache (file).
    this->serverThread = std::make_unique<std::thread>(&XNode::Node::spawnServer,this);
    serverThread->detach();
    log("Server is running!");
    for(const std::string& addr : DNSS){
        attemptBindToNodeServer("ws://"+addr);
    }
}

void XNode::Node::spawnServer() const {
    drogon::app()
            .addListener("0.0.0.0", this->port)
            .setThreadNum(4)
            .run();
    else{
        // Set up the websocket client.
        setupWebSocketClient();
        // Run  the websocket client.
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
    // Set up the server string to which the client will connect to.
    const std::string serverString("ws://" + this->ip + ":" + std::to_string(this->port));
    const std::string path("/hello");

    // Initialize the WebSocketClient
    drogon::WebSocketClientPtr wsPtr = drogon::WebSocketClient::newWebSocketClient(serverString);

    // Initialize the Http request
    drogon::HttpRequestPtr req = drogon::HttpRequest::newHttpRequest();

    // Apply the path to the request.
    req->setPath(path);

    //Handle the response from the websocket server.
    wsPtr->setMessageHandler([](const std::string &message,
                                const drogon::WebSocketClientPtr &,
                                const drogon::WebSocketMessageType &type) {

        std::cout << "new message: " << message;
    });

    // Handle the WebSocket connection closed event.
    wsPtr->setConnectionClosedHandler([](const drogon::WebSocketClientPtr &) {
        std::cout << "WebSocket connection closed!";
    });
}


std::string XNode::node::giveIp(std::string name){
    std::string ret = name2ip[name];
    if (ret==""){
        return "None";
    }
    std::string payload = XNode::Interface::exportDNSHandshake(prunedDNSList);
    wsPtr->send(payload,drogon::WebSocketMessageType::Binary);
}

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
void XNode::node::sendNew(std::string ip, std::string new_name, std::string new_ip){
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
