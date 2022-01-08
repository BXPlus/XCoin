//
// Created by youssef on 11/28/21.
//

#include "transactionPool.h"

bool TransactionPool::isValidTxForPool(Transaction tx, std::vector<Transaction> aTransactionPool)
{
    std::vector<TxIn> txPoolIns = getTxPoolIns(aTransactionPool);
    for(int i = 0; i < (tx.txIns).size(); i++){
        TxIn txIn = tx.txIns[i];
        bool txPoolContainsTxIn = false;
        for(int j = 0; j < txPoolIns.size(); j++){
            if (txPoolIns[j].txOutIndex == txIn.txOutIndex && txPoolIns[j].txOutId == txIn.txOutId){
                txPoolContainsTxIn = true;
            }
        }
        if (txPoolContainsTxIn){
            std::cout << "txIn already found in the txPool";
            return false;
        };
    };
    return true;
}

void TransactionPool::addToTransactionPool(Transaction tx, std::vector<UnspentTxOut> unspentTxOuts) {
    /*if (!tx.validateTransaction(unspentTxOuts)) {
        std::cout << "Trying to add invalid tx to pool 1";
        return;
    }*/
    if (!isValidTxForPool(tx, transactionPool)) {
        std::cout << "Trying to add invalid tx to pool 2";
        return;
    }
    std::cout << "Adding transaction to transactionPool"; //Add details about the transaction by implementing JSON.stringify(tx)
    transactionPool.push_back(tx);
    return;
}

bool TransactionPool::hasTxIn(TxIn txIn, std::vector<UnspentTxOut> unspentTxOuts) {
    for (int i = 0; i < int(unspentTxOuts.size()); i++) {
        UnspentTxOut uTxO = unspentTxOuts[i];
        if (uTxO.txOutId == txIn.txOutId && uTxO.txOutIndex == txIn.txOutIndex) {
            return true;
        }
    }
    return false;
}

void TransactionPool::updateTransactionPool(std::vector<UnspentTxOut> unspentTxOuts) {
    std::vector<Transaction> invalidTxs;
    std::vector<Transaction> newPool;
    for (int i = 0; i < transactionPool.size(); i++) {
        Transaction tx = transactionPool[i];
        bool isValid = true;
        for (int j = 0; j < (tx.txIns).size(); j++) {
            TxIn txIn = (tx.txIns)[j];
            if (!hasTxIn(txIn, unspentTxOuts)) {
                invalidTxs.push_back(tx);
                isValid = false;
                break;
            }
        }
        if (isValid) {
            newPool.push_back(tx);
        }
    }
    if (!invalidTxs.empty()){
        std::cout << "Removing the following transactions from txPool:"; //Here we add the elements in invalidTxs;
        transactionPool = newPool;
    }
}

std::vector<TxIn> TransactionPool::getTxPoolIns(const std::vector<Transaction>& aTransactionPool) {
    std::vector<TxIn> res;
    for (auto & i : aTransactionPool){
        std::vector<TxIn> tx_txIns = i.txIns;
        res.insert(res.end(), tx_txIns.begin(), tx_txIns.end());
    }
    return res;
}
