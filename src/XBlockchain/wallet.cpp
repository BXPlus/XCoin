//
// Created by youssef on 12/5/21.
//
#include "wallet.h"
#include <algorithm>

// Generate and store the private Key

std::string generatePrivateKey() //MALO
{
    return ""; //To implement using key
}

std::string getPrivateFromWallet() //MALO
{
    return "";
}

std::string getPublicFromWallet() //MALO
{
    std::string privateKey = getPrivateFromWallet();
    std::string key; //add when implemented in transaction
    return ""; //Public key in the keyPair encoded.
}

// Wallet Balance

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

std::vector<TxOut> createTxOuts(std::string receiverAddress, std::string myAddress, int amount, int leftOverAmount) {
    TxOut txOut1 = TxOut(receiverAddress, amount);
    std::vector<TxOut> res;
    res.push_back(txOut1);
    if (leftOverAmount == 0) {
        return res;
    } else {
        TxOut leftOverTx = TxOut(myAddress, leftOverAmount);
        res.push_back(leftOverTx);
        return res;
    }
//    TxOut txOut1 = new TxOut(receiverAddress, amount);
//    if (leftOverAmount === 0) {
//        return [txOut1]
//    } else {
//        TxOut leftOverTx = new TxOut(myAddress, leftOverAmount);
//        return [txOut1, leftOverTx];
}

std::vector<TxIn> getTxPoolIns(std::vector<Transaction> aTransactionPool) {
    std::vector<TxIn> res;
    for (int i = 0; i < aTransactionPool.size(); i++){
        std::vector<TxIn> tx_txIns = aTransactionPool[i].txIns;
        res.insert(res.end(), tx_txIns.begin(), tx_txIns.end());
    }
    return res;
}

std::vector<UnspentTxOut> filterTxPoolTxs(std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> transactionPool)
{
    std::vector<UnspentTxOut> newUnspentTxOuts;
    std::vector<TxIn> txIns = getTxPoolIns(transactionPool);
    for (int i = 0; i < unspentTxOuts.size(); i++){
        UnspentTxOut unspentTxOut = unspentTxOuts[i];
        bool removable = true;
        for (int j = 0; j < txIns.size(); j++){
            TxIn txIn = txIns[j];
            if (txIn.txOutIndex == unspentTxOut.txOutIndex && txIn.txOutId == unspentTxOut.txOutId) {
                removable = false;
                break;
            }
        };
        if (removable){
            std::cout << "Removing unspentTxOut from unspentTxOuts" << std::endl;
        } else {
            newUnspentTxOuts.push_back(unspentTxOut);
        }
    }
    return newUnspentTxOuts;
}

TxIn toUnsignedTxIn(UnspentTxOut unspentTxOut) {
    TxIn txIn = TxIn();
    txIn.txOutId = unspentTxOut.txOutId;
    txIn.txOutIndex = unspentTxOut.txOutIndex;
    return txIn;
}

std::vector<TxIn> toUnsignedTxInArray(std::vector<UnspentTxOut> unspentTxOuts) {
    std::vector<TxIn> res;
    for (int i = 0; i < unspentTxOuts.size(); i++) {
        res.push_back(toUnsignedTxIn(unspentTxOuts[i]));
    };
    return res;
}


Transaction createTransaction(std::string receiverAddress, int amount, std::string privateKey, std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> txPool)
{
    std::cout<< "txPool" << std::endl;
    std::string myAddress = getPublicKey(privateKey);
    std::vector<UnspentTxOut> myUnspentTxOutsA = findUnspentTxOuts(myAddress, unspentTxOuts);

    std::vector<UnspentTxOut> myUnspentTxOuts = filterTxPoolTxs(myUnspentTxOutsA, txPool);

    std::vector<UnspentTxOut> includedUnspentTxOuts;
    int leftOverAmount;
    std::tie(includedUnspentTxOuts, leftOverAmount) = findTxOutsForAmount(amount, myUnspentTxOuts);

    std::vector<TxIn> unsignedTxIns = toUnsignedTxInArray(includedUnspentTxOuts);

    Transaction tx;
    tx.txIns = unsignedTxIns;
    tx.txOuts = createTxOuts(receiverAddress, myAddress, amount, leftOverAmount);
    tx.id = tx.getTransactionId();

    //Signing the txIns
    for(int i = 0; i < tx.txIns.size(); i++){
        TxIn txIn = tx.txIns[i];
        txIn.signature = tx.signTxIn(i, privateKey, unspentTxOuts);
    }

    return tx;
}