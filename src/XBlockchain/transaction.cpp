//
// Created by youssef on 11/8/21.
//

#include "transaction.h"


TxOut::TxOut(string address, int amount) {
    this -> address = address;
    this -> amount = amount;
}

<template> <typename T> T* extend_array(T* array, int length, int new_length)
    // This function will handle the txIns_array and the txOuts_array
    // This was inspired from Tutorial 3
{
    T* newArray = new T[new_length];
    for (int i = 0; i < new_size; i++) {
        if (i < length) {
            newArray[i] = array[i];
        } else {
            newArray[i] = 0;
        }
    }
    delete[] array;
    return newArray;
}

<template> <typename T> void T* append_to_array(T element, T* &array, int &current_size, int &max_size)
    // This function will handle the txIns_array and the txOuts_array
    // This was inspired from Tutorial 3
{
    if (current_size == max_size) {
        array = extend_array(array, max_size, max_size+5);
        max_size += 5;
    }
    array[current_size] = element;
    current_size += 1;
}

string Transaction::getTransactionId() {
    stringstream txInsContent;
    for (int i = 0; i < txIns_current_length; i++) {
        element = txIns_array[i];
        txInsContent << element.txOutId << string(element.txOutIndex);
    }
    stringstream txOutsContent;
    for (int i = 0; i < txOuts_current_length; i++) {
        element = txOuts_array[i];
        txOutsContent << element.address << element.amount;
    }
    return sha256(txInsContent.str() + txOutsContent.str());
}

string Transaction::signTxIn(int txInIndex, string privateKey, vector<UnspentTxOut> aUnspentTxOuts) {
    TxIn txIn = txIns_array[txInIndex];
    string dataToSign = id;
    UnspentTxOut referencedUnspentTxOut = findUnspentTxOut(txIn.txOutId, txIn.txOutIndex, aUnspentTxOuts);
    string referencedAddress = referencedUnspentTxOut.address;
    string key;
    string signature; //TODO: Add ECDSA cryptography
    return signature;

}

UnspentTxOut::UnspentTxOut(string txOutID, int txOutIndex, string address, int amount) {
    this -> txOutID = txOutID;
    this -> txOutIndex = txOutIndex;
    this -> address = address;
    this -> amount = amount;
}

UnspentTxOut findUnspentTxOut(string transactionId, int index, vector<UnspentTxOut>& aUnspentTxOuts) {
    for (int id = 0; id < int(aUnspentTxOuts.size()); id++) {
        if (aUnspentTxOuts[id].txOutId == transactionId && aUnspentTxOuts[id].txOutIndex == index)
            return aUnspentTxOuts[id];
    }
    return 0;
}

vector<UnspentTxOut> updateUnspentTxOuts(vector<Transaction> aTransactions, vector<UnspentTxOut> aUnspentTxOuts) {
    vector<UnspentTxOut> newUnspentTxOuts;
    for (int i = 0; i < int(aTransactions.size()); i++) {
        Transaction T = aTransactions[i];
        for (int j = 0; j < T.txOuts_current_length; j++)
            newUnspentTxOuts.push_back(UnspentTxOut(T.id, j, T.txOuts_array[j].address, T.txOuts_array[j].amount);
    }

    vector<UnspentTxOut> consumedTxOuts;
    for (int i = 0; i < int(aTransactions.size()); i++) {
        Transaction T = aTransactions[i];
        for (int j = 0; j < T.txIns_current_length; j++)
            consumedTxOuts.push_back(UnspentTxOut(T.txIns_array[j].txOutId, T.txIns_array[j].txOutIndex, "", 0);
    }

    //Removing the consumedTxOuts elements
    vector<bool> removed(int(aUnspentTxOuts.size()), 0);
    for (int i = 0; i < int(aUnspentTxOuts.size()); i++) {
        if (findUnspentTxOut(aUnspentTxOuts[i].txOutId, aUnspentTxOuts[i].txOutIndex, consumedTxOuts) == 0)
            newUnspentTxOuts.push_back(aUnspentTxOuts[i]);
    }

    return newUnspentTxOuts;
}

bool isValidTxInStructure(TxIn txIn) {
    if ((*txIn) == nullptr) {
        cout << "txIn is null";
        return false;
    }
    else if (typeid(txIn.signature) != typeid("String")) {
        cout << "invalid signature type in txIn";
        return false;
    }
    else if (typeid(txIn.txOutId) != typeid("string")) {
        cout << "invalid txOutId type in txIn";
        return false;
    }
    else if (typeid(txIn.txOutIndex) !== typeid(0)) {
        cout << "invalid txOutIndex type in txIn";
        return false;
    }
    else
        return true;
}


bool isValidAddress(string address) {
    //TODO: Implement this function to verify an address
    // valid address is a valid ecdsa public key in the 04 + X-coordinate + Y-coordinate format
}

bool isValidTxOutStructure(TxOut txOut) {
    if ((*txOut) == nullptr) {
        cout << "txOut is null";
        return false;
    }
    else if (typeid(txOut.address) != typeid("String")) {
        cout << "invalid address type in txOut";
        return false;
    }
    else if (!isValidAddress(txOut.address)) {
        cout << "invalid TxOut address";
        return false;
    }
    else if (typeid(txOut.amount) != typeid(0)) {
        cout << "invalid amount type in txOut";
        return false;
    }
    else
        return true;
}

bool isValidTransactionStructure(Transaction transaction) {
    if (typeid(transaction.id) != typeid("string")) {
        cout << "transactionId missing";
        return false;
    }

    int thisisanarray[5]; //TODO: See if there's better way to validate array type.
    if (typeid(transaction.txIns) != typeid(thisisanarray)) {
        cout << "invalid txIns type in transaction";
        return false;
    }

    bool isValid = 1;
    for (int i = 0; i < transaction.txIns_current_length; i++)
        isValid &= isValidTxInStructure(transaction.txIns_array[i]);

    if (!isValid) {
        cout << "invalid TxIns array";
        return false;
    }

    if (typeid(transaction.txOuts) != typeid(thisisanarray)) {
        cout << "invalid txOuts type in transaction";
        return false;
    }

    isValid = 1;
    for (int i = 0; i < transaction.txOuts_current_length; i++)
        isValid &= isValidTxOutStructure(transaction.txOuts_array[i]);

    if (!isValid) {
        cout << "invalid TxOuts array";
        return false;
    }

    return true;
}