//
// Created by Cyrus Pellet on 04/11/2021.
//

#include <iostream>
#include "node.h"
#include "keys.h"

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
    /*
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
    */
    Keys key =  Keys();
    //std::cout << key.getPriv() << std::endl;
   //std::cout << key.getPub() << std::endl;

    std::string priv = "3DAE35FDCAA5338F6CDD1E13AC2400B654CCADA13A7F8133D079E26A1CC0D202";
    std::string pub = "04923B77634E4227516240612F729286FB44FFBF1FE6954628DCCDCB9962CB42825ADD808F5A4781BC487B592AB8DD6F31773678D5FA064483B63D673A254862B5";
    std::pair<uint8_t*, uint32_t> sgn = sign(priv, "message");


    std::cout << (typeid(sgn) == typeid(std::pair<uint8_t, uint32_t>)) << "  ,  " << sgn.second << std::endl;



}