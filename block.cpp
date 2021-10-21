#include "block.h"

Block::Block(int index, string hash, string previousHash, time_t timestamp, string data) {
    this->index = index;
    this->previousHash = previousHash;
    this->timestamp = timestamp;
    this->data = data;
    this->hash = hash;
}

string Block::calculateHash(int index, string previousHash, time_t timestamp, string data) {
    stringstream ss;
    ss << index << previousHash << timestamp << data;
    return sha256(ss.str()); //We still have to include the license for this
}

string Block::calculateHashForBlock() {
    return Block::calculateHash(index, previousHash, timestamp, data);
}

Block::~Block()
{
}

