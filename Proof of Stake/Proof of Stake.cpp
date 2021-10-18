// Proof of Stake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include "Block.h"
#include "sha256.h"

#include <iostream>
#include <chrono>

int main()
{
    std::cout << sha256(std::to_string(0) + "" + std::to_string(1465154705) + "Genesis block");
}

std::string CalculateHash(int index, std::string previousHash, long timestamp, std::string data) {
    return sha256(std::to_string(index) + previousHash + std::to_string(timestamp) + data);
}

Block::Block(int index, std::string hash, std::string previousHash, long timestamp, std::string data) {
    this->index = index;
    this->hash = hash;
    this->previousHash = previousHash;
    this->timestamp = timestamp;
    this->data = data;
}

Block Block::GenerateNextBlock(std::string data) {
    const long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    const std::string hash = CalculateHash(this->index + 1, this->hash, timestamp, data);
    return Block(this->index , hash, this->hash, timestamp, data);
}

bool Block::IsValidNewBlock(Block &previous) {
    return previous.index + 1 == this->index && previous.hash != this->hash && CalculateHash(this->index, previous.hash, this->timestamp, this->data) == this->hash;
}

bool Block::operator==(Block const& rhs) {
    return this->index == rhs.index && this->hash == rhs.hash && this->previousHash == rhs.previousHash && this->timestamp == rhs.timestamp && this->data == rhs.data;
}
