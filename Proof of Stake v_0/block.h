#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <sstream>
#include "sha256.h" // Include license for this
#include <math.h>
#include "bignumber.h" // Include license for this
#include "bignumber.cpp"

using namespace std;

//Constants //Find somewhere to put this
const int mintingWithoutCoinIndex = 100; //change this

// in seconds
const int BLOCK_GENERATION_INTERVAL = 10; //We will see about this later //We have to adapt this for the type time_t

// in blocks
const int DIFFICULTY_ADJUSTMENT_INTERVAL = 10; //We will see about this later

class Block
{
public:
    //Constructor
    Block(); //This has to be done
    Block(int index, string hash, string previousHash, time_t timestamp, string data,  int dificulty, \
          int minterBalance, string minterAddress);
    ~Block(); //This has to be done

    //Elements for a minimal working block
    int index;
    string hash;
    string previousHash;
    static time_t getCurrentTimestamp();
    time_t timestamp;
    string data;

    //Elements for proof of stake
    int difficulty;
    int nonce;
    int minterBalance;
    string minterAddress;


    //Hash calculator
    static string calculateHash(int index, string previousHash, time_t timestamp, string data, int difficulty, \
                                int minterBalance, string minterAddress);
    string calculateHashForBlock();

    //Staking
    static bool isBlockStakingValid(string previousHash, string address, time_t timestamp,
                                    int balance, int difficulty, int index); //Returns true if the block is valid for staking
    static Block findBlock(int index, string previousHash, string data, int difficulty);


};
#endif // BLOCK_H
