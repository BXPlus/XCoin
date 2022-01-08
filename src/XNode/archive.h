//
// Created by Cyrus on 12/5/2021.
//

#ifndef XBLOCKCHAIN_ARCHIVE_H
#define XBLOCKCHAIN_ARCHIVE_H

#include <iostream>
#include <fstream>
#include <filesystem>

class Archive {
public:
    Archive(const std::string& localPath);
    bool exists();
    void deleteLocalData();
    void saveData(const std::string& encodedData);
    std::string loadData();
private:
    std::filesystem::path localPath;
};


#endif //XBLOCKCHAIN_ARCHIVE_H
