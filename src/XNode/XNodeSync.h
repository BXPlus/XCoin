//
// Created by Kevin on 18/11/2021.
//

#ifndef XBLOCKCHAIN_XNODESYNC_H
#define XBLOCKCHAIN_XNODESYNC_H
#include "Blockchain.h"

/**
 * XNodeSync is a class that is used to synchronize the the user's blockchain with the network.
 * It will give the structure to make the synchronization process effective.
 */
class XNodeSync {
public:
    XNodeSync(Blockchain &blockchain);
    ~XNodeSync();

    void headFirstDownload();
    Blockchain blockDownload();
private:
    Blockchain localBlockchain;
};


#endif //XBLOCKCHAIN_XNODESYNC_H
