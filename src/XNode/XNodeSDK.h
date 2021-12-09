//
// Created by Cyrus on 12/7/2021.
//

#ifndef XBLOCKCHAIN_XNODESDK_H
#define XBLOCKCHAIN_XNODESDK_H


class XNodeSDK {
public:
    enum XNodeStatus {Down, WaitingForDNSS, SyncingBlockchain, Ready, TerminatedWithError};
    virtual void onPeerListChanged(){};
    virtual void onStatusChanged(XNodeStatus status){};
};


#endif //XBLOCKCHAIN_XNODESDK_H
