//
// Created by Cyrus on 11/14/2021.
//

#include "gtest/gtest.h"
#include "../interface.h"

class XNodeCoreTests: public ::testing::Test{
protected:
    Interface interface;
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
    string convertedBlock = interface.encodeBlock(block);
    Block convertedBackBlock = interface.decodeProtobuf(convertedBlock);
    ASSERT_EQ(block, convertedBackBlock);
}