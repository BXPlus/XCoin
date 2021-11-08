//
// Created by youssef on 11/8/21.
//

#include "transaction.h"


TxOut::TxOut(string address, int amount) {
    this->address = address;
    this->amount = amount;
}