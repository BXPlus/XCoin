
#include "block.h"

Block::Block(int index, string hash, string previousHash, time_t timestamp, string data, int difficulty, int minterBalance, string minterAddress) {
    //Elements for minimal working
    this->index = index;
    this->previousHash = previousHash;
    this->timestamp = timestamp;
    this->data = data;
    this->hash = hash;
    //Elements for proof of stake
    this->difficulty = difficulty;
    this->minterBalance = minterBalance;
    this->minterAddress = minterAddress;
}

static time_t getCurrentTimestamp() {
    return time(0); //Test this
}

string Block::calculateHash(int index, string previousHash, time_t timestamp, string data, int difficulty, int minterBalance, string minterAddress) {
    stringstream ss;
    ss << index << previousHash << timestamp << data << difficulty << minterBalance << minterAddress;
    return sha256(ss.str());
}

string Block::calculateHashForBlock() {
    return Block::calculateHash(index, previousHash, timestamp, data, difficulty, minterBalance, minterAddress);
}

//Staking


BigNumber hexToBigNumber(string number) {
    BigNumber res = BigNumber(0);
    for (int i = number.size(); i >=0; i--) {
        int t;
        if ( number[i] == 0 ) {
            t = 0;
        } else if ( number[i] == '1' ) {
            t = 1;
        } else if ( number[i] == '2' ) {
            t = 2;
        } else if ( number[i] == '3' ) {
            t = 3;
        } else if ( number[i] == '4' ) {
            t = 4;
        } else if ( number[i] == '5' ) {
            t = 5;
        } else if ( number[i] == '6' ) {
            t = 6;
        } else if ( number[i] == '7' ) {
            t = 7;
        } else if ( number[i] == '8' ) {
            t = 8;
        } else if ( number[i] == '9' ) {
            t = 9;
        } else if ( number[i] == 'a' ) {
            t = 10;
        } else if ( number[i] == 'b' ) {
            t = 11;
        } else if ( number[i] == 'c' ) {
            t = 12;
        } else if ( number[i] == 'd' ) {
            t = 13;
        } else if ( number[i] == 'e' ) {
            t = 14;
        } else {
            t = 15;
        };
        res = res.add(BigNumber(t));
    }
}


static bool isBlockStakingValid(string previousHash, string address, time_t timestamp, //For the moment we are using the attached library to handle bignumbers, if we need a more advanced one in the future we should consider using the BIGNUM library of openssl
                                int balance, int difficulty, int index) {
    difficulty++;
    if (index < mintingWithoutCoinIndex) {
        balance++;
    };
    BigNumber balanceOverDifficulty = (BigNumber(2).pow(256)).multiply(balance).divide(difficulty);
    stringstream ss;
    ss << previousHash << address << timestamp;
    const string stakingHash = sha256(ss.str());
    const BigNumber decimalStakingHash = hexToBigNumber(stakingHash);
    BigNumber difference = balanceOverDifficulty.subtract(decimalStakingHash);

    return not(difference.isNegative());
}

static Block findBlock(int index, string previousHash, string data, int difficulty) {
    time_t pastTimestamp = 0;
    while (true) {
        time_t timestamp = getCurrentTimestamp();
        if (pastTimestamp != timestamp) {
            string hash = calculateHash(index, previousHash, timestamp, data, difficulty, getAccountBalance(), getPublicFromWallet());
            if (isBlockStakingValid(previousHash, getPublicFromWallet(), timestamp, getAccountBalance(), difficulty, index)) {
                return Block(index, hash, previousHash, timestamp, data, difficulty, getAccountBalance(), getPublicFromWallet());
            }
            pastTimestamp = timestamp;
        }
    }
}


Block::~Block()
{
}

