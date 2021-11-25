#include "transaction.h"
#include "wallet.cpp"
#include <algorithm>

vector<Transaction> transactionPool;

vector<Transaction> getTransactionPool() {
    return transactionPool;
}

/*
 *
Transaction sendTransaction(string address, int amount) {
    Transaction tx = createTransaction(address, amount, getPrivateFromWallet(), getUnspentTxOuts(), getTransactionPool());
    addToTransactionPool(tx, getUnspentTxOuts());
    return tx;
}
 */

bool isValidTxForPool(Transaction tx, vector<Transaction> transactionPool)
{
    return true; //To implement
}

void addToTransactionPool(Transaction tx, vector<UnspentTxOut> unspentTxOuts) {
    if (!tx.validateTransaction(unspentTxOuts)) {
        cout << "Trying to add invalid tx to pool";
        return;
    }
    if (!isValidTxForPool(tx, transactionPool)) {
        cout << "Trying to add invalid tx to pool";
        return;
    }
    //Add a console log
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
    for (int i = 0; i < int(transactionPool.size()); i++) {
        Transaction tx = transactionPool[i];
        for (int j = 0; j < int((tx.txIns).size()); j++) {
            TxIn txIn = (tx.txIns)[j];
            if (!hasTxIn(txIn, unspentTxOuts)) {
                invalidTxs.push_back(tx);
                break;
            }
        }
    }
    if (invalidTxs.size() > 0){
        cout << "Removing the following transactions from txPool:"; //Here we add the elements in invalidTxs;
        for (int i = 0; i < int(invalidTxs.size()); i++) {
            Transaction tx = invalidTxs[i];
            //remove(transactionPool.begin(), transactionPool.end(), tx);
        }
    }
}

vector<TxIn> getTxPoolIns(vector<Transaction> aTransactionPool) {
    vector<TxIn> res;
    for (int i = 0; i < int(aTransactionPool.size()); i++){
        vector<TxIn> tx_txIns = aTransactionPool[i].txIns;
        res.insert(res.end(), tx_txIns.begin(), tx_txIns.end());
    } //To do: Find a way to flatten vectors
    return res;
}

