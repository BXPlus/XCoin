#include "Blockchain.h"

/****************************
**** ChainNode elements ****
****************************/

//Constructor

ChainNode::ChainNode(const Block& block, ChainNode *prev) : block(block)
{
    this->block = block;
    this->prev = prev;
}

/****************************
**** Blockchain elements ****
****************************/

//Constructor

Blockchain::Blockchain()
{
    ChainNode* genesisNode = new ChainNode(genesisBlock, nullptr);
    head = genesisNode;
    tail = genesisNode;
    length = 1;
}

//Generating Blocks

Block Blockchain::generateNextBlock(const string& blockData, int new_difficulty, int minterBalance, string minterAddress)
{
    const Block previousBlock = getLatestBlock();
    const int nextIndex = previousBlock.index + 1;
    const long long nextTimestamp = getCurrentTimestamp();
    const string nextHash = calculateHash(nextIndex, previousBlock.hash, nextTimestamp, blockData, new_difficulty, minterBalance, minterAddress);
    const Block newBlock = Block(nextIndex, nextHash, previousBlock.hash, nextTimestamp, blockData, new_difficulty, minterBalance, minterAddress);
    return newBlock;
}

Block Blockchain::getLatestBlock()
{
    return (*tail).block;
}

void Blockchain::appendBlock(const Block& block)
{
    ChainNode *prev = tail;
    ChainNode* newNode = new ChainNode(block, prev);
    tail = newNode;
    length++;
    updateDifficulty();
}

bool Blockchain::isValidNewBlock(Block newBlock, Block previousBlock)
{
    if (previousBlock.index + 1 == newBlock.index &&
        previousBlock.hash == newBlock.previousHash &&
        newBlock.calculateHashForBlock() == newBlock.hash)
    {
        return true;
    }
    else
    {
        return false;
    };
}

//Checking if the chain is valid

bool Blockchain::isValidChain()
{
    ChainNode currentNode = *tail;
    for (int i = 0; i < length - 1; i++)
    {
        if (not(isValidNewBlock(currentNode.block, (*currentNode.prev).block)))
        {
            return false;
        };
        if (i < length - 2)
        {
            currentNode = *currentNode.prev;
        };
    };
    return true;
}

//Solving conflicts

/*
void Blockchain::replaceChain(Blockchain newChain) {
    if (newChain.isValidChain() && newChain.length > this->length) {
        this->head = newChain.head;
        this->tail = newChain.tail;
        this->length = newChain.length;
    };
}
*/

void Blockchain::replaceChain(Blockchain newChain)
{
    if (newChain.isValidChain() && newChain.getCumulativeDifficulty() > getCumulativeDifficulty()) //The chain with higher cumulative difficulty is the one that stays
    {
        this->head = newChain.head;
        this->tail = newChain.tail;
        this->length = newChain.length;
    };
}

int Blockchain::getCumulativeDifficulty()
{
    ChainNode currentNode = *tail;
    int res = 0;
    for (int i = 0; i < length; i++)
    {
        res += pow(2, currentNode.block.difficulty);
        currentNode = *currentNode.prev;
    };
    return res;
}

//Staking

//Difficulty adjustment

void Blockchain::updateDifficulty()
{
    Block latestBlock = getLatestBlock();
    if (latestBlock.index % DIFFICULTY_ADJUSTMENT_INTERVAL == 0 && latestBlock.index != 0)
    {
        difficulty = getAdjustedDifficulty(latestBlock);
        previousAdjustmentNode = tail;
    }
}

Block Blockchain::getPrevAdjustmentBlock()
{
    return (*previousAdjustmentNode).block;
} // Implement this

int Blockchain::getAdjustedDifficulty(const Block& latestBlock)
{
    const Block prevAdjustmentBlock = getPrevAdjustmentBlock();                          //Implement getPrevAdjustmentBlock using a third pointer pointing to the last block where we checked difficulty
    const int timeExpected = BLOCK_GENERATION_INTERVAL * DIFFICULTY_ADJUSTMENT_INTERVAL; //Check long long type otherwise this makes no sense
    const int timeTaken = latestBlock.timestamp - prevAdjustmentBlock.timestamp;
    if (timeTaken < timeExpected / 2)
    {
        return difficulty + 1;
    }
    else if (timeTaken > timeExpected * 2)
    {
        return difficulty - 1;
    }
    else
    {
        return difficulty;
    }
}

//Validating the timestamp
bool Blockchain::isValidTimestamp(Block newBlock, Block previousBlock)
{
    return (previousBlock.timestamp - 60000 < newBlock.timestamp && newBlock.timestamp - 60000 < getCurrentTimestamp());
};