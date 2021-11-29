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
    //this->serverThread = std::make_unique<std::thread>(&XNode::Node::spawnServer,this);
    //serverThread->detach();
    //log("Server is running!");
    for(const std::string& addr : DNSS){
        attemptBindToNodeServer("ws://"+addr);
    }
    std::getchar();

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

void XNode::Node::attemptBindToNodeServer(const std::string& wsUrl) {
    drogon::WebSocketClientPtr wsPtr = drogon::WebSocketClient::newWebSocketClient(wsUrl);
    wsPtr->setMessageHandler([this, &wsPtr](const std::string &message,
                                const drogon::WebSocketClientPtr &wsClPtr,
                                const drogon::WebSocketMessageType &wsMsType) {
            this->handleNewMessage(wsPtr->getConnection(), const_cast<std::string &&>(message), wsMsType);
    });
    wsPtr->setConnectionClosedHandler([this](const drogon::WebSocketClientPtr &wsClPtr){
        this->handleConnectionClosed(wsClPtr->getConnection());
    });

    // Handle the WebSocket connection closed event.
    wsPtr->setConnectionClosedHandler([](const drogon::WebSocketClientPtr &) {
        std::cout << "WebSocket connection closed!";
    });

    std::cout << "Connecting to WebSocket at " << this->ip;

    // Connect to the websocket server.
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
}


std::string XNode::node::giveIp(std::string name){
    std::string ret = name2ip[name];
    if (ret==""){
        return "None";
    }    std::string payload = XNode::Interface::exportDNSHandshake(prunedDNSList, true);
    wsPtr->send(payload,drogon::WebSocketMessageType::Binary);
}

}

void XNode::Node::handleNewMessage(const drogon::WebSocketConnectionPtr &wsPtr, std::string &&message,
                                   const drogon::WebSocketMessageType &msgType) {
    log("Got message from " + wsPtr->peerAddr().toIpPort());
    try{
        XNodeMessageDecodingResult res = XNode::Interface::decodeXNodeMessageEnvelope(message);
        if (res.messageType == 0){
            log("Got DNS handshake from " + wsPtr->peerAddr().toIpPort());
        } else if (res.messageType == -1){
            log("Invalid message received from " + wsPtr->peerAddr().toIpPort());
        }
    } catch (std::exception &e){
        log("Error decoding message from from " + wsPtr->peerAddr().toIpPort());
    }
}

void XNode::Node::handleNewConnection(const drogon::HttpRequestPtr &reqPtr, const drogon::WebSocketConnectionPtr &wsPtr) {
    std::string addr = wsPtr->peerAddr().toIpPort();
    log(addr + " connected successfully");
    if (this->peers.count(addr) == 0){
        this->peers[addr] = XNode::XNodeClientData(addr, wsPtr);
    }
    //attemptDNSSHandshake(wsPtr);
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
