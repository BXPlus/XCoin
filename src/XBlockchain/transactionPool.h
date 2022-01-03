//
// Created by youssef on 11/28/21.
//

#include "transaction.h"
#include "wallet.h"
#include <algorithm>

std::vector<Transaction> transactionPool;

std::vector<Transaction> getTransactionPool();

Transaction sendTransaction(std::string address, int amount);

bool isValidTxForPool(Transaction tx, std::vector<Transaction> aTransactionPool);

void addToTransactionPool(Transaction tx, std::vector<UnspentTxOut> unspentTxOuts);

bool hasTxIn(TxIn txIn, std::vector<UnspentTxOut> unspentTxOuts);

void updateTransactionPool(std::vector<UnspentTxOut> unspentTxOuts);