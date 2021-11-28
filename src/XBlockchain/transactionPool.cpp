#include "transaction.h"
#include "wallet.cpp"
#include <algorithm>

vector<Transaction> transactionPool;

vector<Transaction> getTransactionPool() {
    return transactionPool;
}

/*
Transaction sendTransaction(string address, int amount) {
    Transaction tx = createTransaction(address, amount, getPrivateFromWallet(), getUnspentTxOuts(), getTransactionPool());
    addToTransactionPool(tx, getUnspentTxOuts());
    return tx;
}
*/

void addToTransactionPool(Transaction tx, vector<UnspentTxOut> unspentTxOuts) {
    if (!tx.validateTransaction(unspentTxOuts)) {
        cout << "Trying to add invalid tx to pool";
        return;
    }
    if (!isValidTxForPool(tx, transactionPool)) {
        cout << "Trying to add invalid tx to pool";
        return;
    }
    cout << "Adding transaction to transactionPool" //Add details about the transaction by implementing JSON.stringify(tx)
    transactionPool.push_back(tx);
    return;
}

bool hasTxIn(TxIn txIn, vector<UnspentTxOut> unspentTxOuts) {
    for (int i = 0; i < int(unspentTxOuts.size()); i++) {
        UnspentTxOut uTxO = unspentTxOuts[i];
        if (uTxO.txOutId == txIn.txOutId && uTxO.txOutIndex == txIn.txOutIndex) {
            return true;
        }
    }
    return false;
}

void updateTransactionPool(vector<UnspentTxOut> unspentTxOuts) {
    vector<Transaction> invalidTxs;
    vector<Transaction> newPool;
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
    if (invalidTxs.size() > 0){
        cout << "Removing the following transactions from txPool:"; //Here we add the elements in invalidTxs;
        transactionPool = newPool;
    }
}

vector<TxIn> getTxPoolIns(vector<Transaction> aTransactionPool) {
    vector<TxIn> res;
    for (int i = 0; i < aTransactionPool.size(); i++){
        vector<TxIn> tx_txIns = aTransactionPool[i].txIns;
        res.insert(res.end(), tx_txIns.begin(), tx_txIns.end());
    }
    return res;
}

bool isValidTxForPool(Transaction tx, vector<Transaction> aTransactionPool)
{
    vector<TxIn> txPoolIns = getTxPoolIns(aTransactionPool);
    for(int i = 0; i < (tx.txIns).size(); i++){
        txIn = txIns[i];
        bool txPoolContainsTxIn = false;
        for(int j = 0; j < txPoolIns.size(); j++){
            if (txPoolIns[j].txOutIndex == txIn.txOutIndex && txPoolIns[j].txOutId == txIn.txOutId){
                txPoolContainsTxIn = true;
            }
        }
        if (txPoolContainsTxIn){
            cout << "txIn already found in the txPool";
            return false
        };
    };
    return true;
}


