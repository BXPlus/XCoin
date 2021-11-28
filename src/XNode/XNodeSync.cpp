//
// Created by Kevin on 18/11/2021.
//

#include "XNodeSync.h"
#include "Blockchain.h"
/**
 * headFirstDownload is a function that downloads the best header chain of the network.
 */
void XNodeSync::headFirstDownload() {
    ChainNode *curBlockPtr = localBlockchain.head;
    Block curBlock = curBlockPtr->block;
    while (curBlockPtr != localBlockchain.tail) {
        //curBlockPtr = curBlockPtr->block;
        curBlock = curBlockPtr->block;
        if (curBlock.hash != curBlock.previousHash) {
            std::cout << "Error: The hash of the previous block is not the same as the hash of the current block." << std::endl;
            return;
        }
    }
}

/**
 * blockDownload is a function that downloads the blocks in parallel corresponding to the header chain.
 * @return the blocks as a block chain.
 */
Blockchain XNodeSync::blockDownload() {
    return Blockchain();
}

/**
 * Copy by reference the local blockchain to apply synchronization changes directly on it.
 * @param blockchain
 */
XNodeSync::XNodeSync(Blockchain &blockchain) {
    this->localBlockchain = blockchain;
}
