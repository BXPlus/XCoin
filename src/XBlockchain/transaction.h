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
    friend bool operator<(const TxIn& txIn1, const TxIn& txIn2) {
        return txIn1.txOutId < txIn2.txOutId;
    }
    int getTxInAmount(std::vector<UnspentTxOut> aUnspentTxOuts);
    std::string JSONStringify();
    TxIn(std::string txOutId, int txOutIndex, std::pair<uint8_t*, uint32_t> signature);
};

class Transaction {
public:
    std::string id;
    std::vector<TxIn> txIns;
    std::vector<TxOut> txOuts;
    std::string getTransactionId();
    std::pair<uint8_t*, uint32_t> signTxIn(int txInIndex, std::string privateKey, std::vector<UnspentTxOut> aUnspentTxOuts);
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

bool validateBlockTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex);

bool hasDuplicates(std::vector<TxIn> txIns);

bool validateTxIn(TxIn txIn, Transaction transaction, std::vector<UnspentTxOut> aUnspentTxOuts);

std::vector<UnspentTxOut> processTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex);

#endif //XCOIN_TRANSACTION_H
