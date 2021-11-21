//
// Created by kevin on 11/15/21.
//

#ifndef XBLOCKCHAIN_XNODEWS_H
#define XBLOCKCHAIN_XNODEWS_H

#include <drogon/WebSocketController.h>

using namespace drogon;

/************************************************************************************
 *
 *  XNodeWS stands for XNode WebSocket and is the main Web Socket controller for XNode.
 *  It will be used by the WebSocket server to handle all WebSocket requests from clients.
 *  It will provide a simple interface for the client to interact with another user.
 *  To use it either as a websocket client or server, you need to uncomment de relevant
 *  lines in the main.cpp file.
 *
 ************************************************************************************/

class XNodeWS : public WebSocketController<XNodeWS> {
public:
    // Those functions are overriden from WebSocketController which is a base class of XNodeWS.
    virtual void handleNewMessage(const WebSocketConnectionPtr&,
                                  std::string &&,
                                  const WebSocketMessageType &)override;
    virtual void handleNewConnection(const HttpRequestPtr &,
                                     const WebSocketConnectionPtr&)override;
    virtual void handleConnectionClosed(const WebSocketConnectionPtr&)override;
    WS_PATH_LIST_BEGIN
        // Example of a path
        WS_PATH_ADD("/hello");
        // TODO: Add the paths here
    WS_PATH_LIST_END
};


#endif //XBLOCKCHAIN_XNODEWS_H
