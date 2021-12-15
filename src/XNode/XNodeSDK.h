//
// Created by Cyrus on 12/7/2021.
//

#ifndef XBLOCKCHAIN_XNODESDK_H
#define XBLOCKCHAIN_XNODESDK_H


class XNodeSDK {
public:
    enum XNodeStatus {Down, WaitingForDNSS, SyncingBlockchain, Ready, TerminatedWithError};
    std::function<void()> onPeerListChanged;
    std::function<void(XNodeStatus)> onStatusChanged;
};


#endif //XBLOCKCHAIN_XNODESDK_H
