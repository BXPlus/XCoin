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
