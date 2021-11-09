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
};


#endif //XCOIN_TRANSACTION_H
