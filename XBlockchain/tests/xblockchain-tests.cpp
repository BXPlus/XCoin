//
// Created by Cyrus Pellet on 25/10/2021.
//

#include "gtest/gtest.h"
#include "../Blockchain.h"

TEST(XBlockchainCore, BlockchainInit) {
    Blockchain bc = Blockchain();
    EXPECT_STREQ(bc.getLatestBlock().hash.c_str(), bc.genesisBlock.hash.c_str());
}
