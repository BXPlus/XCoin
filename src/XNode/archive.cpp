//
// Created by Cyrus on 12/5/2021.
//

#include "archive.h"

Archive::Archive(const std::string& localPath) {
    this->localPath = localPath;
}

bool Archive::exists() {
    return std::filesystem::exists(this->localPath);
}

void Archive::saveData(const std::string& encodedData) {
    std::filesystem::create_directories(this->localPath);
    std::ofstream ofs(this->localPath);
    ofs << encodedData;
    ofs.close();
}

std::string Archive::loadData() {
    std::string res;
    std::ifstream ifs(this->localPath);
    ifs >> res;
    return res;
}
