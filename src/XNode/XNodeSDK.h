//
// Created by Cyrus on 12/7/2021.
//

#ifndef XBLOCKCHAIN_XNODESDK_H
#define XBLOCKCHAIN_XNODESDK_H
#include "archive.h"
#include <vector>

class XNodeSDK {
public:
    enum XNodeStatus {Down, WaitingForDNSS, SyncingBlockchain, Ready, TerminatedWithError};
    std::function<void()> onPeerListChanged;
    std::function<void(XNodeStatus)> onStatusChanged;
    struct XNodeSettings{
        int nodePort;
        std::vector<std::string> rootDNSAddresses;
        std::string publicAddress;
        bool lightNode;
        bool darkThemeEnabled;
    };
    void setNodePort(int newPort);
    int getNodePort();

    void setRootDNSAddresses(std::vector<std::string> newRoot);
    std::vector<std::string> getRootDNSAddresses();

    void setPublicAddress(std::string newAddress);
    std::string getPublicAddress();

    bool getLightNode();
    void setLightNode(bool newLight);

    bool getDarkThemeEnabled();
    void setDarkThemeEnabled(bool newTheme);

    // constructor for XNodeSDK
    XNodeSDK();
private:
    void saveNodeSettings(XNodeSettings newSettings);
    XNodeSettings loadNodeSettings();
    XNodeSettings currentSettings;
    XNodeSettings defaultSettings;
    Archive settingsfile;
};
std::ostream& operator<<(std::ostream &os, const struct XNodeSDK::XNodeSettings &settings);
std::istream& operator>>(std::istream &is, struct XNodeSDK::XNodeSettings &settings);

#endif //XBLOCKCHAIN_XNODESDK_H