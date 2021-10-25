//
// Created by Cyrus Pellet on 25/10/2021.
//

#include "gtest/gtest.h"
#include "../Blockchain.h"

TEST(XBlockchainCore, BlockchainInit) {
    ASSERT_NO_THROW(Blockchain bc = Blockchain());
}
