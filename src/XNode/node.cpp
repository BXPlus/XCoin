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
<<<<<<<<< Temporary merge branch 1
    this->name2ip = std::map<std::string, std::string>();


    /*
     *
     * Request the list of Nodes of the DNS seed
     *
     */
    std::map<std::string, std::string> received ;  //the received dictionary

    name2ip = received;
    this->name2ip["self"] = ip;



=========
    this->peers = std::map<std::string, XNodeClientData>();
    // COmmit
>>>>>>>>> Temporary merge branch 2
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
    }
<<<<<<<<< Temporary merge branch 1
    return ret;
=========
    std::string payload = XNode::Interface::exportDNSHandshake(prunedDNSList, true);
    wsPtr->send(payload,drogon::WebSocketMessageType::Binary);
}
>>>>>>>>> Temporary merge branch 2

}

<<<<<<<<< Temporary merge branch 1
void XNode::node::addNode(std::string name, std::string ip) {

    if (name2ip.find("name") != name2ip.end()){
        return;
    }
    name2ip[name] = ip;
    for (std::map<std::string, std::string>::iterator i = name2ip.begin(); i != name2ip.end(); ++i){
        sendNew(i->second, name, ip);
=========
void XNode::Node::handleNewMessage(const drogon::WebSocketConnectionPtr &wsPtr, std::string &&message,
                                   const drogon::WebSocketMessageType &msgType) {
    try{
        XNodeMessageDecodingResult res = XNode::Interface::decodeXNodeMessageEnvelope(message);
        if (res.messageType == 0){
            log("Got DNS handshake from " + wsPtr->peerAddr().toIpPort());
        } else if (res.messageType == -1){
            log("Invalid message received from " + wsPtr->peerAddr().toIpPort());
        }
    } catch (std::exception &e){
        log("Invalid message received from " + wsPtr->peerAddr().toIpPort());
>>>>>>>>> Temporary merge branch 2
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
