//
// Created by kevin on 11/15/21.
//

#include "XNodeWS.h"
#include "XNode.h"
#include "interface.h"

/**
 * Function handling incoming messages from the client websocket.
 * @param wsConnPtr is the pointer of the websocket connection.
 * @param message is the message received from the client.
 * @param messageType is a value indicating the type of message received.
 */
void XNodeWS::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                               const WebSocketMessageType &messageType) {
    // Sends back the message to the client.
    wsConnPtr->send("you sent me :" + message);
}

/**
 * Function handling a new connection to the server websocket.
 * @param req is the request received from the client.
 * @param wsConnPtr is the pointer of the websocket connection.
 */
void XNodeWS::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    // Sends a message to the client indicating his address and that the connection was successful.
    wsConnPtr->send("Welcome " + req->getPeerAddr().toIpPort() + ". Successful connection!");

    wsConnPtr->send(XNode::Interface::exportChain(XNode::XNode::getBlockchain().toBlocks()));
}

/**
 * Function handling a closed connection to the server websocket.
 * @param wsConnPtr is the pointer of the websocket connection.
 */
void XNodeWS::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    // Sends a message to the client indicating that the connection was closed.
    wsConnPtr->send("Connection closed!");
}
