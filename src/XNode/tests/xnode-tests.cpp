//
// Created by Cyrus on 11/14/2021.
//

#include "gtest/gtest.h"
#include "../interface.h"

class XNodeCoreTests: public ::testing::Test{
protected:
    xcoin::interface interface;
    Blockchain blockchain;
    void SetUp() override{
        interface.startup();
    }
    void TearDown() override{
        interface.shutdown();
    }
};

TEST_F(XNodeCoreTests, ProtobufBlockConversion){
    Block block = blockchain.genesisBlock;
    std::string convertedBlock = interface.exportBlock(block);
    Block convertedBackBlock = interface.importBlock(convertedBlock);
    ASSERT_EQ(block.headerHash, convertedBackBlock.headerHash);
}