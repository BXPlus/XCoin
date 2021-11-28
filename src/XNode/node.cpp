//
// Created by kevin on 11/13/21.
//
#include "node.h"

#include <memory>

/**
 * Constructor for the node class. Starts up a node on the XCoin network.
 * @param DNSS is a list of potential DNS seeds to query on startup
 * @param port is the port to use, 4143 by default
 */

XNode::node::node(const int port) {
    this->port = port;
    this->blockchain = Blockchain();
    this->peerAddrs = std::map<std::string, std::string>();
    this->peerSockets = std::map<std::string, drogon::WebSocketClientPtr>();
}

void XNode::node::start(const std::vector<std::string>& DNSS) {
    //TODO : Fetch Blockchain from cache (file).
    //TODO : Fetch dict from DNSS.
    //this->serverThread = std::make_unique<std::thread>(&XNode::node::spawnServer,this);
    //serverThread->detach();
    //log("Server is running!");
    for(std::string addr : DNSS){
        //attemptBindToNodeServer("ws://"+addr);
    }
    spawnServer();
}

void XNode::node::spawnServer() {
    log("Server will start");
    drogon::app()
            .addListener("0.0.0.0", this->port)
            .setThreadNum(4)
            .run();
}


void XNode::node::stop() {
    log("Server will shut down");
    drogon::app().quit();
    this->serverThread.release();
}

void XNode::node::handleIncomingMessage(const std::string &message, const drogon::WebSocketClientPtr &wsClPtr,
                                        const drogon::WebSocketMessageType &wsMsType) {

}

void XNode::node::handleConnectionClosed(const drogon::WebSocketClientPtr &wsClPtr) {

}

void XNode::node::attemptBindToNodeServer(const std::string& wsUrl) {
    drogon::WebSocketClientPtr wsPtr = drogon::WebSocketClient::newWebSocketClient(wsUrl);
    wsPtr->setMessageHandler([this](const std::string &message,
                                const drogon::WebSocketClientPtr &wsClPtr,
                                const drogon::WebSocketMessageType &wsMsType) {
            this->handleIncomingMessage(message,wsClPtr,wsMsType);
    });
    wsPtr->setConnectionClosedHandler([this](const drogon::WebSocketClientPtr &wsClPtr){
        this->handleConnectionClosed(wsClPtr);
    });
    drogon::HttpRequestPtr req = drogon::HttpRequest::newHttpRequest();
    log("Will attempt to connect to: " + wsUrl + "/");
    wsPtr->connectToServer(req, [this, &wsUrl](drogon::ReqResult r,
    const drogon::HttpResponsePtr &,
    const drogon::WebSocketClientPtr &wsPtr){
        if (r != drogon::ReqResult::Ok){
            log("CONN_FAILED:"+wsPtr->getConnection()->peerAddr().toIpPort());
        }
        wsPtr->getConnection()->send("hello");
        std::string addr = wsPtr->getConnection()->peerAddr().toIpPort();
        log("CONNECTED:"+addr);
        this->peerAddrs[addr] = "<unknown>";
        this->peerSockets[addr] = wsPtr;
        attemptDNSSHandshake(wsPtr);
    });
}

std::map<std::string, std::string> XNode::node::attemptDNSSHandshake(drogon::WebSocketClientPtr wsPtr) {
    wsPtr->getConnection()->send("XCO::DNSQUERY");
    return std::map<std::string, std::string>();
}

std::map<std::string, std::string> XNode::node::attemptPublicAddrHandshake(drogon::WebSocketClientPtr wsPtr) {
    return std::map<std::string, std::string>();
}

void XNode::node::log(const std::string& message, const std::string& host) {
    std::cout << host + "    " + message << std::endl;
}
