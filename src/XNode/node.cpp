//
// Created by kevin on 11/13/21.
//
#include "node.h"

/**
 * Constructor for the node class. Starts up a node on the XCoin network.
 * @param DNSS is a list of potential DNS seeds to query on startup
 * @param port is the port to use, 4143 by default
 */

XNode::Node::Node(const int port) {
    this->port = port;
    this->blockchain = Blockchain();
    this->peers = std::map<std::string, XNodeClientData>();
    // COmmit
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
}

void XNode::Node::spawnServer() {
    drogon::app()
            .addListener("0.0.0.0", this->port)
            .setThreadNum(4)
            .run();
}


void XNode::Node::stop() {
    log("Server will shut down");
    drogon::app().quit();
    this->serverThread.release();
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
    drogon::HttpRequestPtr req = drogon::HttpRequest::newHttpRequest();
    req->setPath("/hello");
    log("Will attempt to connect to: " + wsUrl);
    wsPtr->connectToServer(req, [this, &req](drogon::ReqResult r,
    const drogon::HttpResponsePtr &res,
    const drogon::WebSocketClientPtr &wsPtr){
        if (r != drogon::ReqResult::Ok){
            log("CONN_FAILED:"+wsPtr->getConnection()->peerAddr().toIpPort());
        }
        handleNewConnection(req,wsPtr->getConnection());
    });
    drogon::app().run();
}

void XNode::Node::attemptDNSSHandshake(const drogon::WebSocketConnectionPtr& wsPtr) {
    std::map<std::string, std::string> prunedDNSList = std::map<std::string, std::string>();
    for (auto const& elem : this->peers){
        prunedDNSList[elem.first] = elem.second.publicAddr;
    }
    std::string payload = XNode::Interface::exportDNSHandshake(prunedDNSList, true);
    wsPtr->send(payload,drogon::WebSocketMessageType::Binary);
}

void XNode::Node::log(const std::string& message, const std::string& host) {
    std::cout << host + "    " + message << std::endl;
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

void XNode::Node::handleConnectionClosed(const drogon::WebSocketConnectionPtr &wsPtr) {
    std::string addr = wsPtr->peerAddr().toIpPort();
    if (this->peers.count(addr) != 0){
        this->peers.erase(addr);
    }
}
