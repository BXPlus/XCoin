#include "blockchain.h"

ChainNode::ChainNode(Block block, ChainNode* prev) {
    this->block = block;
    this->prev = prev;
}


Blockchain::Blockchain()
{
    ChainNode genesisNode = ChainNode(genesisBlock, nullptr);
    ChainNode* genesisNode_p = &genesisNode;
    head = genesisNode_p;
    tail = genesisNode_p;
    length = 1;

}

Block Blockchain::generateNextBlock(string blockData) {
    const Block previousBlock = getLatestBlock();
    const int nextIndex = previousBlock.index + 1;
    const time_t nextTimestamp = Block::getCurrentTimestamp();
    const string nextHash = Block::calculateHash(nextIndex, previousBlock.hash, nextTimestamp, blockData);
    const Block newBlock = Block(nextIndex, nextHash, previousBlock.hash, nextTimestamp, blockData);
    return newBlock;
}

Block Blockchain::getLatestBlock() {
    return (*tail).block;
}

void Blockchain::appendBlock(Block block) {
    ChainNode* prev = tail;
    ChainNode newNode = ChainNode(block, prev);
    tail = &newNode;
    length ++;
}

bool Blockchain::isValidNewBlock(Block newBlock, Block previousBlock) {
    if (previousBlock.index+1 == newBlock.index && \
        previousBlock.hash == newBlock.previousHash && \
        newBlock.calculateHashForBlock() == newBlock.hash) {
        return true;
    } else {
        return false;
    };
}

bool Blockchain::isValidChain() {
    ChainNode currentNode = *tail;
    for (int i = 0; i < length-1; i++) {
        if (not(isValidNewBlock(currentNode.block, (*currentNode.prev).block))) {
            return false;
        };
        if (i < length-2) {
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

void Blockchain::replaceChain(Blockchain newChain) {
    if (newChain.isValidChain() && newChain.getCumulativeDifficulty() > getCumulativeDifficulty()) {
        this->head = newChain.head;
        this->tail = newChain.tail;
        this->length = newChain.length;
    };
}

int Blockchain::getCumulativeDifficulty() {
    ChainNode currentNode = *tail;
    int res = 0;
    for (int i = 0; i < length; i++) {
        res += pow(2, currentNode.block.difficulty);
        currentNode = *currentNode.prev;
    };
    return res;
}


//Staking

//Difficulty adjustment

int Blockchain::getDifficulty() {
    Block latestBlock = getLatestBlock();
    if (latestBlock.index%DIFFICULTY_ADJUSTMENT_INTERVAL == 0 && latestBlock.index != 0) {
        return getAdjustedDifficulty(latestBlock);
    } else {
        return latestBlock.difficulty;
    }
}

Block getPrevAdjustmentBlock(){} // Implement this


int Blockchain::getAdjustedDifficulty(Block latestBlock) {
    const Block prevAdjustmentBlock = getPrevAdjustmentBlock(); //Implement getPrevAdjustmentBlock using a third pointer pointing to the last block where we checked difficulty
    const int timeExpected = BLOCK_GENERATION_INTERVAL * DIFFICULTY_ADJUSTMENT_INTERVAL; //Check time_t type otherwise this makes no sense
    const int timeTaken = latestBlock.timestamp - prevAdjustmentBlock.timestamp;
    if (timeTaken < timeExpected / 2) {
        return prevAdjustmentBlock.difficulty + 1;
    } else if (timeTaken > timeExpected * 2) {
        return prevAdjustmentBlock.difficulty - 1;
    } else {
        return prevAdjustmentBlock.difficulty;
    }
}

//Validating the timestamp
bool Blockchain::isValidTimestamp(Block newBlock, Block previousBlock) {
    return (previousBlock.timestamp - 60 < newBlock.timestamp && newBlock.timestamp - 60 < Block::getCurrentTimestamp());
};

