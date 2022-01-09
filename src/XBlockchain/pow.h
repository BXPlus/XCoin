#ifndef POW_H
#define POW_H

/* This is just a skeleton to a potential proof of work consensus mechanism
 * the syntax is just a big global idea, if we were to move on with this for the project, we would
 * further develop and write correctly.
 * This is only a potential skeleton
 * Following an implementation tutorial online https://cryptocurrencyhub.io/implementing-a-simple-proof-of-work-algorithm-for-the-blockchain-bdcd50faac18
 */


#include 'pow.cpp'
#include "sha256.h"    // Include license for this
#include "bignumber.h" // Include license for this
#include <iostream>
#include <sstream>
#include <chrono>
#include <cmath>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

class powblock{
public:
    int index;
    std::string timestamp;
    int data;
    std::string prevHash;
    int difficulty;
    powblock();
    ~powblock();
    std::string calcHash();

    //this is the important part in the Proof of Work: MINING
    powblock mineblock(int difficulty);
};


class powchain{
public:
    int difficulty;
    chain=[];
    powchain(); //constructor
    ~powchain();
    powblock genesisblock(); //create the genesis block
    powblock lastblock(); //return the last block in the chain
    powblock add(); // add a block to the chain
    bool validchain(); //return true or false to see if we have a valid blockchain
};

#endif // POW_H
