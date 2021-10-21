#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <sstream>
#include "sha256.h"

using namespace std;

class Block
{
public:
    Block(); //This has to be done
    Block(int index, string hash, string previousHash, time_t timestamp, string data);
    ~Block();
    int index;
    string hash;
    string previousHash;
    time_t timestamp;
    string data;
    //Hash calculator
    static string calculateHash(int index, string previousHash, time_t timestamp, string data);
    string calculateHashForBlock();
};
#endif // BLOCK_H
