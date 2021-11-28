//
// Created by kevin on 11/15/21.
//

#include "XNodeWS.h"

/**
 * Function handling incoming messages from the client websocket.
 * @param wsConnPtr is the pointer of the websocket connection.
 * @param message is the message received from the client.
 * @param messageType is a value indicating the type of message received.
 */
void XNodeWS::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                               const WebSocketMessageType &messageType) {
    // Sends back the message to the client.
    std::cout << "ACKMSG:" + wsConnPtr->peerAddr().toIpPort() + ":" + message;
}

/**
 * Function handling a new connection to the server websocket.
 * @param req is the request received from the client.
 * @param wsConnPtr is the pointer of the websocket connection.
 */
void XNodeWS::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    // Sends a message to the client indicating his address and that the connection was successful.
    if(req->getPath() == "/terminate"){
        drogon::app().quit();
    }
    wsConnPtr->send("ACK:" + req->getPeerAddr().toIpPort() + ".OK");
    std::cout << "CONN:" + req->getPeerAddr().toIpPort() << std::endl;
    std::vector<Block> blocks = std::vector<Block>();
    blocks.push_back(Blockchain().genesisBlock);
    blocks.push_back(Blockchain().generateNextBlock("This is the second block", 10, 0, ""));
    wsConnPtr->send(XNode::Interface::exportChain(blocks),WebSocketMessageType::Binary);
}

/**
 * Function handling a closed connection to the server websocket.
 * @param wsConnPtr is the pointer of the websocket connection.
 */
void XNodeWS::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    // Sends a message to the client indicating that the connection was closed.
    std::cout << "CLOSED: " + wsConnPtr->peerAddr().toIpPort() << std::endl;
}
