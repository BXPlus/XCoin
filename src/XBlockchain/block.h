#ifndef XCOIN_BLOCK_H
#define XCOIN_BLOCK_H

//Libraries
#include "sha256.h"
#include "bignumber.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <cmath>
#include "transaction.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

/*

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
    Block(int index, std::string hash, std::string previousHash, std::string headerHash, std::string previousHeaderHash, long long timestamp, std::string data, int difficulty, int minterBalance, std::string minterAddress);
    ~Block(); //This has to be done

    //Elements for a minimal working block
    int index;
    std::string hash;
    std::string previousHash;
    std::string headerHash;
    std::string previousHeaderHash;
    long long timestamp; //time in milliseconds
    std::string data;
    int32_t version;
    std::string merkle_root_hash;

    //Elements for proof of stake
    int difficulty;
    int nonce;
    int minterBalance;
    std::string minterAddress;

    //Hash calculator
    std::string calculateHashForBlock();
    std::string calculateHashForHeaders() const;
    std::string calculateMerkleRootHash() const;
};

//Get current time in milliseconds
long long getCurrentTimestamp();

//Hash calculator
std::string calculateHash(int index, std::string previousHash, long long timestamp, std::string data, int difficulty, int minterBalance, std::string minterAddress);
std::string calculateHeaderHash(int32_t version, const std::string& previousBlockHeaderHash, std::string merkle_root_hash, long long time, int nonce);
std::string calculateMerkleHash(const std::string& previousMerkleRootHash, const std::string& transactionHash);
//Staking
bool isBlockStakingValid(std::string previousHash, std::string address, long long timestamp, int balance, int difficulty, int index); //Returns true if the block is valid for staking
Block findBlock(int index, std::string previousHash, std::string previousHeaderHash, std::string previousMerkleHash, std::string data, int difficulty, int nonce);

*/

class Block {
private:
    std::string previousHash;
    long long timestamp;
public:
    Block(int index, std::string hash, std::string previousHash, long long timestamp, Transaction data);
    static long long getCurrentTimestamp();
    Transaction data;
    int index;
    std::string hash;
};

#endif //XCOIN_BLOCK_H

