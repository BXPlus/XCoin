//
// Created by youssef on 11/8/21.
//
#include "block.h"

using namespace std;

#ifndef XCOIN_TRANSACTION_H
#define XCOIN_TRANSACTION_H

class UnspentTxOut {
public:
    const string txOutId;
    const int txOutIndex;
    const string address;
    const int amount;
    UnspentTxOut(string txOutID, int txOutIndex, string address, int amount);
};

class TxIn {
public:
    string txOutId;
    int txOutIndex;
    string signature;
    int getTxInAmount(vector<UnspentTxOut> aUnspentTxOuts);
};


class TxOut {
public:
    string address;
    int amount;
    TxOut(string address, int amount);
    //JSONStringify();
};

class Transaction {
public:
    string id;
    vector<TxIn> txIns;
    vector<TxOut> txOuts;
    string getTransactionId();
    string signTxIn(int txInIndex, string privateKey, vector<UnspentTxOut> aUnspentTxOuts);
    bool hasValidTxIns();
    bool isValidTransactionStructure();
    bool validateCoinbaseTx(int blockIndex);
    bool validateTransaction(vector<UnspentTxOut> aUnspentTxOuts);
};

vector<UnspentTxOut> updateUnspentTxOuts(vector<Transaction> aTransactions, vector<UnspentTxOut> aUnspentTxOuts);

bool isValidTxInStructure(TxIn txIn);

bool isValidAddress(string address);

bool isValidTxOutStructure(TxOut txOut);

Transaction getCoinbaseTransaction(string address, int blockIndex);

string getPublicKey(string aPrivateKey);

bool validateBlockTransactions(vector<Transaction> aTransactions, vector<UnspentTxOut> aUnspentTxOuts, int blockIndex){
    return true; //To Implement
};

bool hasDuplicates(vector<TxIn> txIns){
    return true; //To Implement
}

bool validateTxIn(TxIn txIn, Transaction transaction, vector<UnspentTxOut> aUnspentTxOuts);

pair<bool, UnspentTxOut> findUnspentTxOut(string transactionId, int index, vector<UnspentTxOut>& aUnspentTxOuts);

void processTransactions(vector<Transaction> aTransactions, vector<UnspentTxOut> aUnspentTxOuts, int blockIndex){
    return;
}

#endif //XCOIN_TRANSACTION_H
