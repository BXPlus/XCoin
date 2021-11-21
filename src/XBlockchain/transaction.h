//
// Created by youssef on 11/8/21.
//
#include "block.h"

using namespace std;

#ifndef XCOIN_TRANSACTION_H
#define XCOIN_TRANSACTION_H

class TxOut {
public:
    string address;
    int amount;
    TxOut(string address, int amount);
};

class TxIn {
public:
    string txOutId;
    int txOutIndex;
    string signature;
    int getTxInAmount(vector<UnspentTxOut> aUnspentTxOuts);
    bool validateTxIn(Transaction transaction, vector<UnspentTxOut> aUnspentTxOuts);
};

class Transaction {
public:
    string id;
    vector<TxIn> txIns;
    vector<TxOut> txOuts;
    string getTransactionId();
    string signTxIn(int txInIndex, string privateKey, vector<UnspentTxOut> aUnspentTxOuts);
    bool hasValidTxIns();
    bool validateTransaction(vector<UnspentTxOut> aUnspentTxOuts);
    bool isValidTransactionStructure();
};

class UnspentTxOut {
public:
    string txOutId;
    int txOutIndex;
    string address;
    int amount;
    UnspentTxOut(string txOutID, int txOutIndex, string address, int amount);
}

UnspentTxOut findUnspentTxOut(string transactionId, int index, vector<UnspentTxOut> aUnspentTxOuts);

vector<UnspentTxOut> updateUnspentTxOuts(vector<Transaction> aTransactions, vector<UnspentTxOut> aUnspentTxOuts);

bool isValidTxInStructure(TxIn txIn);

bool isValidAddress(string address);

bool isValidTxOutStructure(TxOut txOut);

#endif //XCOIN_TRANSACTION_H
