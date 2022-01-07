
//
// Created by youssef on 12/5/21.
//

#ifndef XBLOCKCHAIN_WALLET_H
#define XBLOCKCHAIN_WALLET_H

#include "Blockchain.h"
#include "keys.h"
#include "archive.h"
#include "transactionPool.h"


class Wallet {
public:
    Wallet();
    std::string getPrivateFromWallet();

    std::vector<UnspentTxOut> myUnspentTxOuts;
    std::vector<UnspentTxOut> getUnspentTxOuts();
    void setUnspentTxOuts(std::vector<UnspentTxOut> unspentTxOuts);

private:
    Archive dataStorage = Archive("local.xnodekeys");

    std::string generatePrivateKey();
    std::string getPublicFromWallet();
    void initWallet();
    void deleteWallet();
    std::vector<UnspentTxOut> findUnspentTxOuts(std::string ownerAddress, std::vector<UnspentTxOut> unspentTxOuts);
    int getBalance(std::string address, std::vector<UnspentTxOut> unspentTxOuts);
    std::pair<std::vector<UnspentTxOut>,int> findTxOutsForAmount(int amount, std::vector<UnspentTxOut> myUnspentTxOuts);
    std::vector<TxOut> createTxOuts(std::string receiverAddress, std::string myAddress, int amount, int leftOverAmount);
    std::vector<UnspentTxOut> filterTxPoolTxs(std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> transactionPool);
    TxIn toUnsignedTxIn(UnspentTxOut unspentTxOut);
    std::vector<TxIn> toUnsignedTxInArray(std::vector<UnspentTxOut> unspentTxOuts);
    Transaction createTransaction(std::string receiverAddress, int amount, std::string privateKey, std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> txPool);
    Transaction sendTransaction(std::string address, int amount);
    Transaction mintCoinbaseTransaction(int amount);

    TransactionPool myTransactionPool;
    std::vector<Transaction> getTransactionPool();
    std::vector<TxIn> getTxPoolIns();

    Transaction createGenesisTransaction();
    Transaction genesisTransaction = createGenesisTransaction();

    Block createGenesisBlock();
    Block genesisBlock = createGenesisBlock();

    Blockchain myBlockchain = Blockchain(genesisBlock);

    void addBlockToChain(Transaction data);
};

#endif //XBLOCKCHAIN_WALLET_H

