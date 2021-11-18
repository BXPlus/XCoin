//
// Created by kevin on 11/14/21.
//

#ifndef XCOIN_XNODECTL_H
#define XCOIN_XNODECTL_H

#include <drogon/HttpController.h>
#include "interface.h"
#include "Blockchain.h"

/************************************************************************************
 *
 *  xnodectl stands for XNode Controller and is the main Http controller for XNode.
 *  The purpose of this Http controller is to provide a simple interface for
 *  implementing the Networking.
 *  It is supposed to evolve in the near future into a WebSocket controller, but me (Kevin)
 *  will be in charge of converting it to a WebSocket controller.
 *  To access the page, use the following url: http://0.0.0.0/api/xnodectl/{*endpoint*}.
 *  Be aware that the ip address 0.0.0.0 will be replaced by the actual ip address of the device,
 *  in the future.
 *
 ************************************************************************************/
namespace api {
    /***
     * To add endpoints to the controller, you need to add a new macro
     * METHOD_ADD(xnodectl::{*your_function*}, "/{*your_endpoint*}/{{*some_arguments_if_needed*}}", drogon::Get);
     * I (Kevin) implemented you a an example of a simple endpoint that returns a JSON message, and a bit more complex
     * endpoint that takes and argument and prints it back.
     */
    class xnodectl : public drogon::HttpController<xnodectl> {
    public:
        // Endpoint paths go here
        METHOD_LIST_BEGIN
            // Example endpoint path
            METHOD_ADD(xnodectl::printHello, "/hello", drogon::Get);
            METHOD_ADD(xnodectl::printHelloComplex, "/hello/{name}", drogon::Get);
            // TODO: Insert your endpoint paths here

        METHOD_LIST_END

        // Endpoint functions go here
        // Example endpoint function
        void printHello(const drogon::HttpRequestPtr &req,
                        std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;

        void printHelloComplex(const drogon::HttpRequestPtr &req,
                               std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                               const std::string &name) const;
        // TODO: Insert your endpoint functions here

        void printBlocks(const drogon::HttpRequestPtr &req,
                         std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;

    };
}


#endif //XCOIN_XNODECTL_H
