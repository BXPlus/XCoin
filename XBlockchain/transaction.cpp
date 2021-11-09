//
// Created by youssef on 11/8/21.
//

#include "transaction.h"


TxOut::TxOut(string address, int amount) {
    this->address = address;
    this->amount = amount;
}

<template> <typename T> T* extend_array(T* array, int length, int new_length)
    // This function will handle the txIns_array and the txOuts_array
    // This was inspired from Tutorial 3
{
    T* newArray = new T[new_length];
    for (int i; i < new_size; i++) {
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
    };
    array[current_size] = element;
    current_size += 1;
}

string Transaction::getTransactionId() {
    stringstream txInsContent;
    for (int i; i < txIns_current_length; i++) {
        element = txIns_array[i];
        txInsContent << element.txOutId << string(element.txOutIndex);
    }
    stringstream txOutsContent;
    for (int i; i < txOuts_current_length; i++) {
        element = txOuts_array[i];
        txOutsContent << element.address << element.amount;
    }
    return sha256(txInsContent.str() + txOutsContent.str());
}
