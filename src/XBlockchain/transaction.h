//
// Created by XCoin on 11/8/21.
//

#ifndef XCOIN_TRANSACTION_H
#define XCOIN_TRANSACTION_H

#include <map>
#include "block.h"

#include "../XNode/keys.h"
/*
//Delete later zone
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include "openssl/sha.h"

class Keys {
public:
    Keys(); //constructor which creates the private and public key randomly
    Keys(std::string pubb); //constructor which creates a key from a public key
    Keys(EC_KEY *key); //constructor from an EC_KEY object


    char const* getPriv(){
        //returns the hexadecimal fom of the private key
        return priv_key;
    }
    char const* getPub(){
        //returns the hexadecimal fom of the public key
        return pub_key;
    }

private:
    BIGNUM const* prv;        //private key (which is a big integer)
    char const* priv_key;         //private key in hexadecimal form
    EC_POINT const* pub;      //public key which is a point made of two coordinates and depending on the private key
    char const* pub_key;         //public key in hexadecimal form

};

//FREE FUNCTIONS

Keys keyFromPrivate(std::string priv_keyy);
//return a key from a private key

Keys keyFromPublic(std::string address);
//returns a key whose public key is address

std::pair<uint8_t*, uint32_t> sign(std::string priv_key, std::string dataToSign);
/*
 * Computes the signature of a given data with a given private key:
 *      INPUTS:
 *          - pkey : a private key
 *          - dataToSign : the data we want to make a signature of
 *
 *      OUTPUTS:
 *          a pair of data:
 *          -first (array of uint8_t) is the signature
 *          - Second is the length of the signature
 */

bool verify(std::pair<uint8_t*, uint32_t> signature, std::string pub_key, std::string id);
/*
 * Verifies whether the signature has been signed by a given public key
 *      INPUTS:
 *          - a pair of <Signature, signature_length>
 *          - a public key
 *          - id : the data which has been signed
 *      OUTPUTS:
 *          - 0 if the data hasn't been signed by this public key or if it is not the data which has been signed
 *          - 1 if everything is correct
 */

//Delete later zone

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
    friend bool operator<(const TxIn& txIn1, const TxIn& txIn2) {
        return txIn1.txOutId < txIn2.txOutId;
    }
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
};

std::pair<bool, UnspentTxOut> findUnspentTxOut(std::string transactionId, int index, std::vector<UnspentTxOut>& aUnspentTxOuts); //added test

std::vector<UnspentTxOut> updateUnspentTxOuts(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts);

bool isValidTxInStructure(TxIn txIn);

bool isValidAddress(std::string address); //added test

bool isValidTxOutStructure(TxOut txOut);

Transaction getCoinbaseTransaction(std::string address, int blockIndex); //added test

std::string getPublicKey(std::string aPrivateKey);

bool hasDuplicates(std::vector<TxIn> txIns); //added test

bool validateBlockTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex);

std::vector<UnspentTxOut> processTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex);

#endif //XCOIN_TRANSACTION_H
