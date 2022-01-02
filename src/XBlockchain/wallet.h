
//
// Created by youssef on 12/5/21.
//

#include "transaction.h"
#include "keys.h"
#include "archive.h"

#ifndef XBLOCKCHAIN_WALLET_H
#define XBLOCKCHAIN_WALLET_H


class Wallet {
public:
    Wallet();
    std::string getPrivateFromWallet();

private:
    Archive dataStorage = Archive("local.xnodekeys");

};




std::string generatePrivateKey();

std::string getPrivateFromWallet();

std::string getPublicFromWallet();

void initWallet();

void deleteWallet();

std::vector<UnspentTxOut> findUnspentTxOuts(std::string ownerAddress, std::vector<UnspentTxOut> unspentTxOuts);

int getBalance(std::string address, std::vector<UnspentTxOut> unspentTxOuts);

std::pair<std::vector<UnspentTxOut>,int> findTxOutsForAmount(int amount, std::vector<UnspentTxOut> myUnspentTxOuts);

std::vector<TxOut> createTxOuts(std::string receiverAddress, std::string myAddress, int amount, int leftOverAmount);

std::vector<TxIn> getTxPoolIns(std::vector<Transaction> aTransactionPool);

std::vector<UnspentTxOut> filterTxPoolTxs(std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> transactionPool);

TxIn toUnsignedTxIn(UnspentTxOut unspentTxOut);

std::vector<TxIn> toUnsignedTxInArray(std::vector<UnspentTxOut> unspentTxOuts);

Transaction createTransaction(std::string receiverAddress, int amount, std::string privateKey, std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> txPool);

#endif //XBLOCKCHAIN_WALLET_H

