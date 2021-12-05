//
// Created by Cyrus Pellet on 04/11/2021.
//

#include <iostream>
#include "node.h"

int main(int argc, char *argv[])
{
    std::string banner = " __   __   ____     _____    ______   __  __     \n"
                         "/\\ \\ /\\ \\ /\\  _`\\  /\\  __`\\ /\\__  _\\ /\\ \\/\\ \\    \n"
                         "\\ `\\`\\/'/'\\ \\ \\/\\_\\\\ \\ \\/\\ \\\\/_/\\ \\/ \\ \\ `\\\\ \\   \n"
                         " `\\/ > <   \\ \\ \\/_/_\\ \\ \\ \\ \\  \\ \\ \\  \\ \\ , ` \\  \n"
                         "    \\/'/\\`\\ \\ \\ \\L\\ \\\\ \\ \\_\\ \\  \\_\\ \\__\\ \\ \\`\\ \\ \n"
                         "    /\\_\\\\ \\_\\\\ \\____/ \\ \\_____\\ /\\_____\\\\ \\_\\ \\_\\\n"
                         "    \\/_/ \\/_/ \\/___/   \\/_____/ \\/_____/ \\/_/\\/_/";
    std::cout << banner << std::endl;
    std::cout << "                                  Blockchain node    \n" << std::endl;
    std::vector<std::string> DNSS = std::vector<std::string>();
    for(int i = 1; i < argc; i++ )
        DNSS.emplace_back(argv[i]);
    XNode::Node node = XNode::Node();
    node.start(DNSS);
    char u;
    while (true){
        std::cin >> std::ws >> u;
        if (u == 'q')
            std::cout << "Node will terminate..." << std::endl;
        break;
    }
    return 0;
}