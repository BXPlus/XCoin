//
// Created by Cyrus Pellet on 04/11/2021.
//

#include <iostream>
#include "XNode.h"

std::string banner = " __   __   ____     _____    ______   __  __     \n"
                "/\\ \\ /\\ \\ /\\  _`\\  /\\  __`\\ /\\__  _\\ /\\ \\/\\ \\    \n"
                "\\ `\\`\\/'/'\\ \\ \\/\\_\\\\ \\ \\/\\ \\\\/_/\\ \\/ \\ \\ `\\\\ \\   \n"
                " `\\/ > <   \\ \\ \\/_/_\\ \\ \\ \\ \\  \\ \\ \\  \\ \\ , ` \\  \n"
                "    \\/'/\\`\\ \\ \\ \\L\\ \\\\ \\ \\_\\ \\  \\_\\ \\__\\ \\ \\`\\ \\ \n"
                "    /\\_\\\\ \\_\\\\ \\____/ \\ \\_____\\ /\\_____\\\\ \\_\\ \\_\\\n"
                "    \\/_/ \\/_/ \\/___/   \\/_____/ \\/_____/ \\/_/\\/_/";

int main()
{
    const std::string ip = "0.0.0.0";
    const int port = 80;
    std::cout << banner << std::endl;
    std::cout << "                                  Blockchain node    \n" << std::endl;

    /**************************************************************************************/
    // To set up a classical HttpController, uncomment the following lines:

    /*std::cout << "Server will start on "<< ip << " and listens to the port " << port << std::endl;
    XNode node = XNode(ip, port);*/

    /**************************************************************************************/

    /**************************************************************************************/
    // To set up a WebSocket client, uncomment the following lines:

    /*std::cout << "Websocket client will connect to "<< ip << " on the port " << port << std::endl;
    XNode node = XNode(ip, port, true, false);*/

    /**************************************************************************************/

    /**************************************************************************************/
    // To set up a WebSocket server, uncomment the following lines:

    std::cout << "Websocket server will start on "<< ip << " and listens to the port " << port << std::endl;
    XNode node = XNode(ip, port, true, true);

    /**************************************************************************************/

    // Start the server
    node.start();

    return 0;
}