#ifndef XCOIN_BLOCK_H
#define XCOIN_BLOCK_H

//Libraries
#include "sha256.h"    // Include license for this
#include "bignumber.h" // Include license for this
#include <iostream>
#include <sstream>
#include <chrono>
#include <cmath>

using namespace std;

using chrono::duration_cast;
using chrono::milliseconds;
using chrono::seconds;
using chrono::system_clock;

//Constants //Find somewhere to put this
const int mintingWithoutCoinIndex = 100; //change this

// in seconds
const int BLOCK_GENERATION_INTERVAL = 10; //We will see about this later //We have to adapt this for the type long long

// in blocks
const int DIFFICULTY_ADJUSTMENT_INTERVAL = 10; //We will see about this later

class Block
{
public:
    //Constructor
    Block(int index, string hash, string previousHash, long long timestamp, string data, int difficulty, int minterBalance, string minterAddress);
    ~Block(); //This has to be done

    //Elements for a minimal working block
    int index;
    string hash;
    string previousHash;
    long long timestamp; //time in milliseconds
    string data;
    int32_t version;
    char32_t merkle_root_hash;

    //Elements for proof of stake
    int difficulty;
    int nonce;
    int minterBalance;
    string minterAddress;

    //Hash calculator
    string calculateHashForBlock();
};

//Get current time in milliseconds
long long getCurrentTimestamp();

//Hash calculator
string calculateHash(int index, string previousHash, long long timestamp, string data, int difficulty, int minterBalance, string minterAddress);

//Staking
bool isBlockStakingValid(string previousHash, string address, long long timestamp, int balance, int difficulty, int index); //Returns true if the block is valid for staking
Block findBlock(int index, string previousHash, string data, int difficulty);

#endif //XCOIN_BLOCK_H
