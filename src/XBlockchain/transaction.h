//
// Created by youssef on 11/8/21.
//
#include "block.h"

#ifndef XCOIN_TRANSACTION_H
#define XCOIN_TRANSACTION_H

class UnspentTxOut {
public:
    std::string txOutId;
    int txOutIndex;
    std::string address;
    int amount;
    UnspentTxOut(std::string txOutID, int txOutIndex, std::string address, int amount);
};

class TxOut {
public:
    std::string address;
    int amount;
    TxOut(std::string address, int amount);
};

class TxIn {
public:
    std::string txOutId;
    int txOutIndex;
    std::pair<uint8_t*, uint32_t> signature;
    int getTxInAmount(std::vector<UnspentTxOut> aUnspentTxOuts);
    std::string JSONStringify();
};

class Transaction {
public:
    std::string id;
    std::vector<TxIn> txIns;
    std::vector<TxOut> txOuts;
    std::string getTransactionId();
    std::pair<uint8_t*, uint32_t> signTxIn(int txInIndex, std::string privateKey, std::vector<UnspentTxOut> aUnspentTxOuts);
    bool hasValidTxIns();
    bool validateTransaction(std::vector<UnspentTxOut> aUnspentTxOuts);
    bool isValidTransactionStructure();
    bool validateCoinbaseTx(int blockIndex);
};

std::pair<bool, UnspentTxOut> findUnspentTxOut(std::string transactionId, int index, std::vector<UnspentTxOut>& aUnspentTxOuts);

std::vector<UnspentTxOut> updateUnspentTxOuts(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts);

bool isValidTxInStructure(TxIn txIn);

bool isValidAddress(std::string address);

bool isValidTxOutStructure(TxOut txOut);

Transaction getCoinbaseTransaction(std::string address, int blockIndex);

std::string getPublicKey(std::string aPrivateKey);

bool validateBlockTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex){
    return true; //To Implement
};

bool hasDuplicates(std::vector<TxIn> txIns) {
    return true; //To Implement
}

bool validateTxIn(TxIn txIn, Transaction transaction, std::vector<UnspentTxOut> aUnspentTxOuts);

void processTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex){
    return; //To implement
}

#endif //XCOIN_TRANSACTION_H
