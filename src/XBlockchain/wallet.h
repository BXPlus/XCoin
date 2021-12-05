//
// Created by youssef on 12/5/21.
//

#include "transaction.h"

#ifndef XBLOCKCHAIN_WALLET_H
#define XBLOCKCHAIN_WALLET_H

std::string generatePrivateKey();

std::string getPrivateFromWallet();

std::string getPublicFromWallet();

void initWallet();

void deleteWallet();

std::vector<UnspentTxOut> findUnspentTxOuts(std::string ownerAddress, std::vector<UnspentTxOut> unspentTxOuts);

int getBalance(std::string address, std::vector<UnspentTxOut> unspentTxOuts);

std::pair<std::vector<UnspentTxOut>,int> findTxOutsForAmount(int amount, std::vector<UnspentTxOut> myUnspentTxOuts);

void createTxOuts(std::string receiverAddress, std::string myAddress, int amount, int leftOverAmount);

std::vector<TxIn> getTxPoolIns(std::vector<Transaction> aTransactionPool);

std::vector<UnspentTxOut> filterTxPoolTxs(std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> transactionPool);

#endif //XBLOCKCHAIN_WALLET_H
