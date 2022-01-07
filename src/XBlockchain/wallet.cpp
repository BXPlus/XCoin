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
    const std::string newPrivKey = generatePrivateKey();

    dataStorage.saveData(newPrivKey);
}

/*
void deleteWallet() {
    return;
}
*/

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
    addBlockToChain(tx);
    return tx;
}

void Wallet::setUnspentTxOuts(std::vector<UnspentTxOut> unspentTxOuts) {
    myUnspentTxOuts = unspentTxOuts;
}

Transaction Wallet::createGenesisTransaction() {
    std::pair<uint8_t*, uint32_t> signature = std::pair(nullptr, 0);
    std::string txOutId = "";
    int txOutIndex = 0;
    std::string address = "04bfcab8722991ae774db48f934ca79cfb7dd991229153b9f732ba5334aafcd8e7266e47076996b55a14bf9913ee3145ce0cfc1372ada8ada74bd287450313534a";
    int amount = 50;
    std::string id = "e655f6a5f26dc9b4cac6e46f52336428287759cf81ef5ff10854f69d68f43fa3";
    std::vector<TxIn> txIns;
    txIns.push_back(TxIn(txOutId, txOutIndex, signature));
    std::vector<TxOut> txOuts;
    txOuts.push_back(TxOut(address, amount));
    return Transaction(txIns, txOuts, id);
}

Block Wallet::createGenesisBlock() {
    int index = 0;
    std::string hash = "";
    std::string previousHash = "";
    long long timestamp = 1465154705;
    return Block(index, hash, previousHash, timestamp, genesisTransaction);
}

void Wallet::addBlockToChain(Transaction data) {
    myBlockchain.addBlock(data);
    std::vector<Transaction> aTransactions;
    aTransactions.push_back(data);
    Block newBlock = myBlockchain.getLatestBlock();
    std::vector<UnspentTxOut> retVal = processTransactions(aTransactions, myUnspentTxOuts, newBlock.index);
    setUnspentTxOuts(retVal);
    myTransactionPool.updateTransactionPool(myUnspentTxOuts);
}
