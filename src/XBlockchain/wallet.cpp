//
// Created by youssef on 12/5/21.
//

#include "transaction.h"
#include "wallet.h"

//# Generate and store the private Key

std::string generatePrivateKey()
{
    return ""; //To implement using key
}

std::string getPrivateFromWallet()
{
    return "";
}

std::string getPublicFromWallet()
{
    std::string privateKey = getPrivateFromWallet();
    std::string key; //add when implemented in transaction
    return ""; //Public key in the keyPair encoded.
}

//# Wallet Balance

void initWallet() {
    return;
}

void deleteWallet() {
    return;
}



std::string getBalance()
{
    return "";
}




void createTxOuts(std::string receiverAddress, std::string myAddress, int amount, int leftOverAmount) {
//    TxOut txOut1 = new TxOut(receiverAddress, amount);
//    if (leftOverAmount === 0) {
//        return [txOut1]
//    } else {
//        TxOut leftOverTx = new TxOut(myAddress, leftOverAmount);
//        return [txOut1, leftOverTx];
    return;
}
