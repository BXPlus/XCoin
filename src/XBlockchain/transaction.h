//
// Created by youssef on 11/8/21.
//
#include "block.h"

using namespace std;

#ifndef XCOIN_TRANSACTION_H
#define XCOIN_TRANSACTION_H

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
    TxIn* txIns_array;
    int txIns_current_length;
    int txIns_max_length;
    TxOut* txOuts_array;
    int txOuts_current_length;
    int txOuts_max_length;
    string getTransactionId();
    string signTxIn(int txInIndex, string privateKey, vector<UnspentTxOut> aUnspentTxOuts);
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

bool isValidTransactionStructure(Transaction transaction);

#endif //XCOIN_TRANSACTION_H
