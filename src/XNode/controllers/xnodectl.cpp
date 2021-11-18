//
// Created by kevin on 11/14/21.
//

#include "xnodectl.h"

using namespace api;

/**
 * Example of an endpoint that returns a JSON response "Hello world!".
 * @param req is the request object.
 * @param callback is used to send the response back to the client.
 */
void xnodectl::printHello(const drogon::HttpRequestPtr &req,
                          std::function<void(const drogon::HttpResponsePtr &)> &&callback) const {
    Json::Value res;
    res["message"] = "Hello world!";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(res);
    callback(resp);
}

/**
 * Example of an endpoint that returns a JSON response "Hello {*name*}!", where name is an argument passed in the
 * query string.
 * @param req is the request object.
 * @param callback is used to send the response back to the client.
 */
void xnodectl::printHelloComplex(const drogon::HttpRequestPtr &req,
                                 std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                                 const std::string &name) const {
    Json::Value res;
    res["message"] = "Hello " + name + "!";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(res);
    callback(resp);
}

/**
 * /blocks endpoint to list the blockchain's block.
 * Returns a JSON response of strings encoding of blockchain into transferable & storable protobuf data
*/

void xnodectl::printBlocks(const drogon::HttpRequestPtr &req,
                           std::function<void(const drogon::HttpResponsePtr &)> &&callback) const{
   // Block *blocks;
   // blocks = Blockchain.GetBlocks();
   // for (int i = 0; i < sizeof(blocks); i++){
   //    res["message"] += encodeBlock(blocks[i]);
   //}
    Json::Value res;
    res = Blockchain.tail;
    while (res.prev is not nullptr){
        res["message"] += encodeBlock((*res.prev).block)
    }
    auto resp = drogon::HttpResponse::newHttpJsonResponse(res);
    callback(resp);
}


