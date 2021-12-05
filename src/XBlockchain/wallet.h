//
// Created by youssef on 12/5/21.
//

#include "transaction.h"

#ifndef XBLOCKCHAIN_WALLET_H
#define XBLOCKCHAIN_WALLET_H

std::vector<TxIn> getTxPoolIns(std::vector<Transaction> aTransactionPool);

#endif //XBLOCKCHAIN_WALLET_H
