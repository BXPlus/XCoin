//
// Created by youssef on 11/8/21.
//
#include "block.h"

using namespace std;

#ifndef XCOIN_TRANSACTION_H
#define XCOIN_TRANSACTION_H

class UnspentTxOut {
public:
    string txOutId;
    int txOutIndex;
    string address;
    int amount;
    UnspentTxOut(string txOutID, int txOutIndex, string address, int amount);
};

class TxOut
{
public:
    string address;
    int amount;
    TxOut(string address, int amount);
};

class TxIn
{
public:
    string txOutId;
    int txOutIndex;
    string signature;
};

class Transaction {
public:
    string id;
    vector<TxIn> txIns;
    vector<TxOut> txOuts;
    string getTransactionId();
    string signTxIn(int txInIndex, string privateKey, vector<UnspentTxOut> aUnspentTxOuts);
};

UnspentTxOut findUnspentTxOut(string transactionId, int index, vector<UnspentTxOut> aUnspentTxOuts);

vector<UnspentTxOut> updateUnspentTxOuts(vector<Transaction> aTransactions, vector<UnspentTxOut> aUnspentTxOuts);

bool isValidTxInStructure(TxIn txIn);

bool isValidAddress(string address);

bool isValidTxOutStructure(TxOut txOut);

bool isValidTransactionStructure(Transaction transaction);

#endif //XCOIN_TRANSACTION_H
