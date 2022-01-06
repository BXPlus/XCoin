//
// Created by XCoin on 11/8/21.
//

#ifndef XCOIN_TRANSACTION_H
#define XCOIN_TRANSACTION_H

#include <map>
#include <vector>
#include "sha256.h"

#include "keys.h"


class UnspentTxOut {
public:
    std::string txOutId;
    int txOutIndex;
    std::string address;
    int amount;
    bool operator==(const UnspentTxOut& _UnspentTxOut) {
        return (this -> txOutId == _UnspentTxOut.txOutId &&
                this -> txOutIndex == _UnspentTxOut.txOutIndex &&
                this -> address == _UnspentTxOut.address &&
                this -> amount == _UnspentTxOut.amount);
    }
    UnspentTxOut();
    UnspentTxOut(std::string txOutID, int txOutIndex, std::string address, int amount); //added test
};

class TxOut {
public:
    std::string address;
    int amount;
    TxOut();
    TxOut(std::string address, int amount); //added test
};

class TxIn {
public:
    std::string txOutId;
    int txOutIndex;
    std::pair<uint8_t*, uint32_t> signature;
    int getTxInAmount(std::vector<UnspentTxOut> aUnspentTxOuts); //added test
    TxIn();
    TxIn(std::string txOutId, int txOutIndex, std::pair<uint8_t*, uint32_t> signature);//added test
};

bool validateTxIn(TxIn txIn, std::string id, std::vector<UnspentTxOut> aUnspentTxOuts);

class Transaction {
public:
    std::string id;
    std::vector<TxIn> txIns;
    std::vector<TxOut> txOuts;
    std::string getTransactionId(); //added test
    std::pair<uint8_t*, uint32_t> signTxIn(int txInIndex, std::string privateKey, std::vector<UnspentTxOut> aUnspentTxOuts);
    bool validateTransaction(std::vector<UnspentTxOut> aUnspentTxOuts);
    bool isValidTransactionStructure();
    bool validateCoinbaseTx(int blockIndex); //added test
    Transaction();
    Transaction(std::vector<TxIn> txIns, std::vector<TxOut> txOuts, std::string id);
};

std::pair<bool, UnspentTxOut> findUnspentTxOut(std::string transactionId, int index, std::vector<UnspentTxOut>& aUnspentTxOuts); //added test

std::vector<UnspentTxOut> updateUnspentTxOuts(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts);

bool isValidAddress(std::string address); //added test

bool isValidTxOutStructure(TxOut txOut);

Transaction getCoinbaseTransaction(std::string address, int blockIndex); //added test

std::string getPublicKey(std::string aPrivateKey);

bool hasDuplicates(std::vector<TxIn> txIns); //added test

bool validateBlockTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex);

std::vector<UnspentTxOut> processTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex);

#endif //XCOIN_TRANSACTION_H
