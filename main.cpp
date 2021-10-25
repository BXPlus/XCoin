#include <iostream>
#include "XBlockchain/Blockchain.h"

int main() {
    Blockchain bc = Blockchain();
    std::cout << bc.isValidChain() << std::endl;
}
