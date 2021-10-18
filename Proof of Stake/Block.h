#pragma once

#include <string>

class Block {
private:
    int index;
    std::string hash;
    std::string previousHash;
    long timestamp;
    std::string data;
public:
    Block(int index, std::string hash, std::string previousHash, long timestamp, std::string data);
    Block GenerateNextBlock(std::string data);
};