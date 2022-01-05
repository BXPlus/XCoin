//
// Created by Lio Elalouf--Lewiner on 18/12/2021.
//

#include <sstream>
#include "XNodeSDK.h"

XNodeSDK::XNodeSDK(){ // set default settings
    settingsfile = Archive("localsettings.xnodebackup");
    defaultSettings.nodePort= 50051;
    defaultSettings.rootDNSAddresses.emplace_back("129.104.213.110:80");
    defaultSettings.publicAddress = "";
    defaultSettings.lightNode = false;
    defaultSettings.darkThemeEnabled = true;
}


XNodeSDK::XNodeSettings XNodeSDK::loadNodeSettings(){
    if(!settingsfile.exists()){
        currentSettings = defaultSettings;
        saveNodeSettings(defaultSettings); // create file
    }
    std::istringstream filecontent(settingsfile.loadData());
    filecontent >> currentSettings;
    return currentSettings;
}

void XNodeSDK::saveNodeSettings(XNodeSettings newSettings) {
    std::ostringstream settingstring;
    settingstring << newSettings ;
    settingsfile.saveData(settingstring.str());
}
/*
void XNodeSDK::setNodePort(int newPort) {
    currentSettings.nodePort = newPort;
    saveNodeSettings(currentSettings) ;
}
 */
int XNodeSDK::getNodePort(){return currentSettings.nodePort;}

void XNodeSDK::setRootDNSAddresses(std::vector<std::string> newRoot){
    currentSettings.rootDNSAddresses = newRoot;
    saveNodeSettings(currentSettings) ;
}
std::vector<std::string> XNodeSDK::getRootDNSAddresses() {return currentSettings.rootDNSAddresses;}

void XNodeSDK::setPublicAddress(std::string newAddress){
    currentSettings.publicAddress = newAddress;
    saveNodeSettings(currentSettings) ;
}
std::string XNodeSDK::getPublicAddress() {return currentSettings.publicAddress;}

void XNodeSDK::setLightNode(bool newLight) {
    currentSettings.lightNode = newLight;
    saveNodeSettings(currentSettings) ;
}
bool XNodeSDK::getLightNode() {return currentSettings.lightNode;}

void XNodeSDK::setDarkThemeEnabled(bool newTheme) {
    currentSettings.darkThemeEnabled = newTheme;
    saveNodeSettings(currentSettings) ;}
bool XNodeSDK::getDarkThemeEnabled() {return currentSettings.darkThemeEnabled;}



std::ostream& operator<<(std::ostream &os, const struct XNodeSDK::XNodeSettings &settings)
{   os << "nodePort: " << settings.nodePort << "\n";
    os << "rootDNSAddresses: "; // << newSettings.rootDNSAddresses << "\n"; // look result of this encoding
    for (std::vector<std::string>::const_iterator it = settings.rootDNSAddresses.begin();
         it != settings.rootDNSAddresses.end();
         ++it){
        os << "\"" << *it << "\" ";
    }
    os << "\n" ;
    os << "publicAddress: " << settings.publicAddress << "\n";
    os << "lightNode: " << settings.lightNode << "\n";
    os << "darkThemeEnabled: " << settings.darkThemeEnabled << "\n";
    return os;
}

std::istream& operator>>(std::istream &is, struct XNodeSDK::XNodeSettings &settings){
    struct XNodeSDK::XNodeSettings currentSettings ;
    std::string line;
    while (std::getline(is, line)) {
        // std::cout << line << std::endl;
        if (line.rfind("nodePort: ", 0) == 0) { // pos=0 limits the search to the prefix
            // s starts with prefix
            currentSettings.nodePort = stoi(line.substr(10));
        } //do the same for other node settings
        if (line.rfind("rootDNSAddresses: ", 0) == 0) {
            // currentSettings.rootDNSAddresses = stoi(line.substr(18));
            std::string values = line.substr(18) ;
            size_t found = values.find("\"");
            while (found != std::string::npos){
                size_t found2 = values.find("\"", found+1);
                if (found2 == std::string::npos){ break ;}
                std::string value = values.substr(found + 1, found2 - found - 1) ;
                currentSettings.rootDNSAddresses.push_back(value);
                found = values.find("\"", found2+1);
            }
        }
        if (line.rfind("publicAddress: ", 0) == 0) {
            currentSettings.publicAddress = line.substr(15);
        }
        if (line.rfind("lightNode: ", 0) == 0) {
            currentSettings.lightNode = !!(stoi(line.substr(11))); // convert int in bool
        }
        if (line.rfind("darkThemeEnabled: ", 0) == 0) {
            currentSettings.darkThemeEnabled = !!(stoi(line.substr(18)));
        }
    }
    settings = currentSettings;
    return is;
}
