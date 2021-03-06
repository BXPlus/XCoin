#include "block.h"

//Constructor

Block::Block(int index, std::string hash, std::string previousHash, std::string headerHash,  std::string previousHeaderHash, long long timestamp, std::string data, int difficulty, int minterBalance, std::string minterAddress)
{
    //Elements for minimal working
    this->index = index;
    this->previousHash = previousHash;
    this->previousHeaderHash = previousHeaderHash;
    this->timestamp = timestamp;
    this->data = data;
    this->hash = hash;
    this->headerHash = headerHash;
    //Elements for proof of stake
    this->difficulty = difficulty;
    this->minterBalance = minterBalance;
    this->minterAddress = minterAddress;
    version = 1;
    nonce = 1;
}

//Hash calculator

std::string Block::calculateHashForBlock()
{
    return calculateHash(index, previousHash, timestamp, data, difficulty, minterBalance, minterAddress);
}

std::string Block::calculateHashForHeaders() const {
    return calculateHeaderHash(version, previousHeaderHash, merkle_root_hash, timestamp, nonce);
}

std::string Block::calculateMerkleRootHash() const {
    return calculateMerkleHash(previousHeaderHash, hash);
}

/*************************
**** Managing Blocks *****
*************************/

//Get current time in milliseconds

long long getCurrentTimestamp()
{
    long long millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return millisec_since_epoch;
}

//Hash Calculator

std::string calculateHash(int index, std::string previousHash, long long timestamp, std::string data, int difficulty, int minterBalance, std::string minterAddress)
{
    std::stringstream ss;
    ss << index << previousHash << timestamp << data << difficulty << minterBalance << minterAddress;
    return sha256(ss.str());
}

std::string calculateHeaderHash(int32_t version, const std::string& previousBlockHeaderHash, std::string merkle_root_hash, long long time, int nonce){
    std::stringstream ss;
    ss << version << previousBlockHeaderHash << merkle_root_hash << time << nonce;
    return sha256(ss.str());
}

std::string calculateMerkleHash(const std::string& previousMerkleRootHash, const std::string& transactionHash){
    std::stringstream ss;
    ss << previousMerkleRootHash << transactionHash;
    return sha256(ss.str());
}

//Staking

//Converting a hexadecimal std::string into a BigNumber
BigNumber hexToBigNumber(std::string number)
{
    BigNumber res = BigNumber(0);
    for (int i = number.size(); i >= 0; i--)
    {
        int t;
        if (number[i] == 0)
        {
            t = 0;
        }
        else if (number[i] == '1')
        {
            t = 1;
        }
        else if (number[i] == '2')
        {
            t = 2;
        }
        else if (number[i] == '3')
        {
            t = 3;
        }
        else if (number[i] == '4')
        {
            t = 4;
        }
        else if (number[i] == '5')
        {
            t = 5;
        }
        else if (number[i] == '6')
        {
            t = 6;
        }
        else if (number[i] == '7')
        {
            t = 7;
        }
        else if (number[i] == '8')
        {
            t = 8;
        }
        else if (number[i] == '9')
        {
            t = 9;
        }
        else if (number[i] == 'a')
        {
            t = 10;
        }
        else if (number[i] == 'b')
        {
            t = 11;
        }
        else if (number[i] == 'c')
        {
            t = 12;
        }
        else if (number[i] == 'd')
        {
            t = 13;
        }
        else if (number[i] == 'e')
        {
            t = 14;
        }
        else
        {
            t = 15;
        };
        res = res.add(BigNumber(t));
    }
    return res;
}

bool isBlockStakingValid(std::string previousHash, std::string address, long long timestamp, int balance, int difficulty, int index)
{ //For the moment we are using the attached library to handle bignumbers, if we need a more advanced one in the future we should consider using the BIGNUM library of openssl
    difficulty++;
    if (index < mintingWithoutCoinIndex)
    {
        balance++;
    };
    BigNumber balanceOverDifficulty = (BigNumber(2).pow(256)).multiply(balance).divide(difficulty);
    std::stringstream ss;
    ss << previousHash << address << timestamp;
    const std::string stakingHash = sha256(ss.str());
    const BigNumber decimalStakingHash = hexToBigNumber(stakingHash);
    BigNumber difference = balanceOverDifficulty.subtract(decimalStakingHash);

    return !(difference.isNegative());
}

Block findBlock(int index, const std::string& previousHash, const std::string& previousHeaderHash, const std::string& previousMerkleHash, const std::string& data, int difficulty, int accountBalance, const std::string& accountAddress, int nonce)
{
    long long pastTimestamp = 0;
    while (true)
    {
        long long timestamp = getCurrentTimestamp();
        if (pastTimestamp != timestamp)
        {
            std::string hash = calculateHash(index, previousHash, timestamp, data, difficulty, accountBalance, accountAddress);
            std::string headerHash = calculateHeaderHash(1, previousHeaderHash, calculateMerkleHash(previousMerkleHash, hash), timestamp, nonce);
            if (isBlockStakingValid(previousHash, accountAddress, timestamp, accountBalance, difficulty, index))
            {
                return Block(
                        index,
                        hash,
                        previousHash,
                        headerHash,
                        previousHeaderHash,
                        timestamp,
                        data,
                        difficulty,
                        accountBalance,
                        accountAddress);
            }
            pastTimestamp = timestamp;
        }
    }
}

Block::~Block()
= default;