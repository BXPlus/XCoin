//
// Created by Cyrus Pellet on 04/11/2021.
//

#include<iostream>
#include<drogon/drogon.h>
#include "Blockchain.h"

std::string banner = " __   __   ____     _____    ______   __  __     \n"
                "/\\ \\ /\\ \\ /\\  _`\\  /\\  __`\\ /\\__  _\\ /\\ \\/\\ \\    \n"
                "\\ `\\`\\/'/'\\ \\ \\/\\_\\\\ \\ \\/\\ \\\\/_/\\ \\/ \\ \\ `\\\\ \\   \n"
                " `\\/ > <   \\ \\ \\/_/_\\ \\ \\ \\ \\  \\ \\ \\  \\ \\ , ` \\  \n"
                "    \\/'/\\`\\ \\ \\ \\L\\ \\\\ \\ \\_\\ \\  \\_\\ \\__\\ \\ \\`\\ \\ \n"
                "    /\\_\\\\ \\_\\\\ \\____/ \\ \\_____\\ /\\_____\\\\ \\_\\ \\_\\\n"
                "    \\/_/ \\/_/ \\/___/   \\/_____/ \\/_____/ \\/_/\\/_/";

int main()
{
    Blockchain blockchain;
    std::cout << banner << std::endl;
    std::cout << "                                  Blockchain node    \n" << std::endl;
    std::cout << "Server will start..." << std::endl;
    drogon::app().addListener("0.0.0.0",80).enableRunAsDaemon().setThreadNum(16).run();
    return 0;
}