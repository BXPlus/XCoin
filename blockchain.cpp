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
    const time_t nextTimestamp = time(0);
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

void Blockchain::replaceChain(Blockchain newChain) {
    if (newChain.isValidChain() && newChain.length > this->length) {
        this->head = newChain.head;
        this->tail = newChain.tail;
        this->length = newChain.length;
    };
}
