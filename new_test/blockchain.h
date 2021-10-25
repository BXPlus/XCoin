#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"

class ChainNode
{
public:
    ChainNode(Block block, ChainNode *prev);
    Block block;
    ChainNode *prev;
};

class Blockchain
{

public:
    //Constructor
    Blockchain(); //Contructs a blockchain with only one chain node containing the genesis block

    //Manipulating blocks
    Block genesisBlock = Block(0, "816534932c2b7154836da6afc367695e6337db8a921823784c14378abed4f7d7", NULL, 1465154705, "my genesis block!!", 0, 0, "");
    Block getLatestBlock();                                                                             //returns the last block in the chain
    Block generateNextBlock(string blockData, int difficulty, int minterBalance, string minterAddress); //generates the next block given its data, based on the last block in the chain
    void appendBlock(Block block);                                                                      //Add a new node to the chain containing the new block
    bool isValidNewBlock(Block newBlock, Block previousBlock);

    //Implementing the chain
    ChainNode *head;
    ChainNode *tail;
    ChainNode *previousAdjustmentNode;
    int length;
    int difficulty;

    //Validating the chain
    bool isValidChain();

    //Validating the timestamp
    bool isValidTimestamp(Block newBlock, Block previousBlock);

    //Solving conflicts

    //void replaceChain(Blockchain newChain); // Replaces the blockchain by the new chain if it is valid and longer.
    void replaceChain(Blockchain newChain); // Replaces the blockchain by the new chain if its cumulative difficulty is higher. // WHY? “Nakamoto consensus”
    int getCumulativeDifficulty();

    //Staking
    void updateDifficulty();
    int getAdjustedDifficulty(Block latestBlock);
    Block getPrevAdjustmentBlock();
};

#endif // BLOCKCHAIN_H
