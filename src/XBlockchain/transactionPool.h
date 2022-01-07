//
// Created by youssef on 11/28/21.
//

#include "transaction.h"
#include <algorithm>

class TransactionPool {
private:
    bool isValidTxForPool(Transaction tx, std::vector<Transaction> aTransactionPool);
    bool hasTxIn(TxIn txIn, std::vector<UnspentTxOut> unspentTxOuts);
    static std::vector<TxIn> getTxPoolIns(std::vector<Transaction> aTransactionPool);

public:
    std::vector<Transaction> transactionPool;
    void addToTransactionPool(Transaction tx, std::vector<UnspentTxOut> unspentTxOuts);

    void updateTransactionPool(std::vector<UnspentTxOut> unspentTxOuts);
};