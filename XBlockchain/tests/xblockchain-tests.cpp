//
// Created by Cyrus Pellet on 25/10/2021.
//

#include "gtest/gtest.h"
#include "../Blockchain.h"

class XBlockchainCoreTests: public ::testing::Test{
protected:
    Blockchain blockchain;
    void SetUp() override{
        blockchain = Blockchain();
    }
};

// Initialisation test: the blockchain is structured properly after being created
TEST_F(XBlockchainCoreTests, BlockchainInit) {
    EXPECT_EQ(blockchain.tail, blockchain.head);
    EXPECT_EQ(blockchain.getLatestBlock().index, 0);
    EXPECT_STREQ(blockchain.getLatestBlock().data.c_str(), blockchain.genesisBlock.data.c_str());
    EXPECT_EQ(blockchain.getLatestBlock().hash, blockchain.genesisBlock.hash);
    EXPECT_EQ(blockchain.isValidChain(), true);
}

// Generating the next block in the blockchain. Testing if all properties make sense with relation to previous block
TEST_F(XBlockchainCoreTests, BlockchainGenerateBlock){
    Block newBlock = blockchain.generateNextBlock("Second block!",1,100,"abc");
    EXPECT_EQ(newBlock.index,blockchain.getLatestBlock().index+1);
    EXPECT_GT(newBlock.timestamp, blockchain.getLatestBlock().timestamp);
    EXPECT_NE(newBlock.hash, blockchain.getLatestBlock().hash);
}

// Actually adding the new block in the blockchain, testing if it is still valid after
TEST_F(XBlockchainCoreTests, BlockchainAddBlock){
    Block newBlock = blockchain.generateNextBlock("Second block!",10,100,"abc");
    int oldLength = blockchain.length;
    blockchain.appendBlock(newBlock);
    EXPECT_NE(blockchain.getLatestBlock().hash, blockchain.genesisBlock.hash);
    EXPECT_EQ(blockchain.getLatestBlock().hash, newBlock.hash);
    EXPECT_EQ(blockchain.length, oldLength + 1);
    EXPECT_EQ(blockchain.difficulty , 0); // TODO: Make some more extensive tests for this when it works
}