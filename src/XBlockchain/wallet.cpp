//
// Created by youssef on 12/5/21.
//
#include "wallet.h"
#include <algorithm>


// Generate and store the private Key

std::string Wallet::generatePrivateKey()
{
    return Keys().getPriv();
}

std::string Wallet::getPrivateFromWallet()
{
    std::string privKey = dataStorage.loadData();
    return privKey;
}

std::string Wallet::getPublicFromWallet()
{
    std::string privateKey = getPrivateFromWallet();
    return keyFromPrivate(privateKey).getPub();
}

// Wallet Balance

Wallet::Wallet() {
    if(!dataStorage.exists()){
        const std::string newPrivKey = generatePrivateKey();
        dataStorage.saveData(newPrivKey);
    }
}

void Wallet::deleteWallet() {
    this->dataStorage.deleteLocalData();
    myTransactionPool.transactionPool.clear();
}


std::vector<UnspentTxOut> Wallet::findUnspentTxOuts(std::string ownerAddress, std::vector<UnspentTxOut> unspentTxOuts)
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

int Wallet::getBalance(std::string address, std::vector<UnspentTxOut> unspentTxOuts)
{
    std::vector<UnspentTxOut> ownedUnspentTxOuts = findUnspentTxOuts(address, unspentTxOuts);
    int res = 0;
    for (int i = 0; i < ownedUnspentTxOuts.size(); i++){
        UnspentTxOut uTxO = ownedUnspentTxOuts[i];
        res += uTxO.amount;
    };
    return res;
}

std::pair<std::vector<UnspentTxOut>,int> Wallet::findTxOutsForAmount(int amount, std::vector<UnspentTxOut> myUnspentTxOuts)
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

std::vector<TxOut> Wallet::createTxOuts(std::string receiverAddress, std::string myAddress, int amount, int leftOverAmount)
{
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
}

std::vector<TxIn> Wallet::getTxPoolIns()
{
    std::vector<Transaction> aTransactionPool = myTransactionPool.transactionPool;
    std::vector<TxIn> res;
    for (int i = 0; i < aTransactionPool.size(); i++){
        std::vector<TxIn> tx_txIns = aTransactionPool[i].txIns;
        res.insert(res.end(), tx_txIns.begin(), tx_txIns.end());
    }
    return res;
}

std::vector<UnspentTxOut> Wallet::filterTxPoolTxs(std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> transactionPool)
{
    std::vector<UnspentTxOut> newUnspentTxOuts;
    std::vector<TxIn> txIns = getTxPoolIns();
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

TxIn Wallet::toUnsignedTxIn(UnspentTxOut unspentTxOut)
{
    TxIn txIn = TxIn();
    txIn.txOutId = unspentTxOut.txOutId;
    txIn.txOutIndex = unspentTxOut.txOutIndex;
    return txIn;
}

std::vector<TxIn> Wallet::toUnsignedTxInArray(std::vector<UnspentTxOut> unspentTxOuts)
{
    std::vector<TxIn> res;
    for (int i = 0; i < unspentTxOuts.size(); i++) {
        res.push_back(toUnsignedTxIn(unspentTxOuts[i]));
    };
    return res;
}


Transaction Wallet::createTransaction(std::string receiverAddress, int amount, std::string privateKey, std::vector<UnspentTxOut> unspentTxOuts, std::vector<Transaction> txPool)
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

std::vector<Transaction> Wallet::getTransactionPool() {
    return myTransactionPool.transactionPool;
}

std::vector<UnspentTxOut> Wallet::getUnspentTxOuts() {
    return myUnspentTxOuts;
}

Transaction Wallet::sendTransaction(std::string address, int amount) {
    Transaction tx = createTransaction(address, amount, getPrivateFromWallet(), getUnspentTxOuts(), getTransactionPool());
    myTransactionPool.addToTransactionPool(tx, getUnspentTxOuts());
    return tx;
}

Transaction Wallet::mintCoinbaseTransaction(int amount) {
    Transaction tx = getCoinbaseTransaction(getPublicFromWallet() , amount);
    return tx;
}

std::string Wallet::encrypt_data(const Transaction& transaction) {
    std::stringstream ss;
    ss << transaction.id;
    std::vector<TxIn> txIns = transaction.txIns;
    std::vector<TxOut> txOuts = transaction.txOuts;
    for(auto & txIn : txIns){
        ss << txIn.txOutIndex << txIn.txOutId;
    }
    for(auto & txOut : txOuts){
        ss << txOut.address << txOut.amount;
    }
    return sha256(ss.str());
}

Transaction Wallet::commitTransaction(std::string address, int amount, const Block& lastBlock) {
    Transaction tx = createTransaction(std::move(address), amount, getPrivateFromWallet(), getUnspentTxOuts(), getTransactionPool());
    myTransactionPool.addToTransactionPool(tx, getUnspentTxOuts());
    std::string hash = encrypt_data(tx);
    std::vector<Transaction> aTransactions;
    aTransactions.push_back(tx);
    std::vector<UnspentTxOut> retVal = processTransactions(aTransactions, myUnspentTxOuts, lastBlock.index);
    myUnspentTxOuts = retVal;
    myTransactionPool.updateTransactionPool(myUnspentTxOuts);
    return tx;
}
