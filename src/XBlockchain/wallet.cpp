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

std::vector<UnspentTxOut> findUnspentTxOuts(std::string ownerAddress, std::vector<UnspentTxOut> unspentTxOuts)
{
    std::vector<UnspentTxOut> res;
    for (int i = 0; i < unspentTxOuts.size(); i++){
        UnspentTxOut uTxO = unspentTxOuts[i];
        if (uTxO.address == ownerAddress) {
            res.push_back(uTxO);
        };
    }
    return res;
}

int getBalance(std::string address, std::vector<UnspentTxOut> unspentTxOuts)
{
    std::vector<UnspentTxOut> ownedUnspentTxOuts = findUnspentTxOuts(address, unspentTxOuts);
    int res;
    for (int i = 0; i < ownedUnspentTxOuts.size(); i++){
        UnspentTxOut uTxO = ownedUnspentTxOuts[i];
        res += uTxO.amount;
    };
    return res;
}

std::pair<std::vector<UnspentTxOut>,int> findTxOutsForAmount(int amount, std::vector<UnspentTxOut> myUnspentTxOuts)
{
    int currentAmount = 0;
    std::vector<UnspentTxOut> includedUnspentTxOuts;
    for (int i = 0; i < myUnspentTxOuts.size(); i++){
        UnspentTxOut myUnspentTxOut = myUnspentTxOuts[i];
        includedUnspentTxOuts.push_back(myUnspentTxOut);
        currentAmount += myUnspentTxOut.amount;
        if (currentAmount >= amount){
            int leftOverAmount = currentAmount - amount;
            return std::make_pair(includedUnspentTxOuts, leftOverAmount);
        }
    }
    std::string errorMsg = "Cannot create Transaction: insufficient total amount of unspent transaction outputs.";
    throw std::logic_error(errorMsg);
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