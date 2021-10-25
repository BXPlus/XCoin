
#include "block.h"

/*************************
***** Block elements *****
*************************/

//Constructor

Block::Block(int index, string hash, string previousHash, long long timestamp, string data, int difficulty, int minterBalance, string minterAddress)
{
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

//Hash calculator

string Block::calculateHashForBlock()
{
    return calculateHash(index, previousHash, timestamp, data, difficulty, minterBalance, minterAddress);
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

string calculateHash(int index, string previousHash, long long timestamp, string data, int difficulty, int minterBalance, string minterAddress)
{
    stringstream ss;
    ss << index << previousHash << timestamp << data << difficulty << minterBalance << minterAddress;
    return sha256(ss.str());
}

//Staking

//Converting a hexadecimal string into a BigNumber
BigNumber hexToBigNumber(string number)
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
}

bool isBlockStakingValid(string previousHash, string address, long long timestamp, int balance, int difficulty, int index)
{ //For the moment we are using the attached library to handle bignumbers, if we need a more advanced one in the future we should consider using the BIGNUM library of openssl
    difficulty++;
    if (index < mintingWithoutCoinIndex)
    {
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

Block findBlock(int index, string previousHash, string data, int difficulty, int accountBalance, string accountAddress)
{
    long long pastTimestamp = 0;
    while (true)
    {
        long long timestamp = getCurrentTimestamp();
        if (pastTimestamp != timestamp)
        {
            string hash = calculateHash(index, previousHash, timestamp, data, difficulty, accountBalance, accountAddress);
            if (isBlockStakingValid(previousHash, accountAddress, timestamp, accountBalance, difficulty, index))
            {
                return Block(index, hash, previousHash, timestamp, data, difficulty, accountBalance, accountAddress);
            }
            pastTimestamp = timestamp;
        }
    }
}

Block::~Block()
{
}
