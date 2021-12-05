//
// Created by youssef on 11/8/21.
//

#include "transaction.h"
#include "../XNode/keys.h"
#include <stdexcept>
#include "../XNode/keys.h"
#include <regex>

#define fi first
#define se second

const int COINBASE_AMOUNT = 50;

TxOut::TxOut(std::string address, int amount) {
    this -> address = address;
    this -> amount = amount;
}

std::string Transaction::getTransactionId() {
    std::stringstream txInsContent;
    for(int i = 0; i < int(txIns.size()); i++) {
        TxIn element = txIns[i];
        txInsContent << element.txOutId << element.txOutIndex;
    }
    std::stringstream txOutsContent;
    for(int i = 0; i < int(txOuts.size()); i++) {
        TxOut element = txOuts[i];
        txOutsContent << element.address << element.amount;
    }
    return sha256(txInsContent.str() + txOutsContent.str());
}

std::pair<bool, UnspentTxOut> findUnspentTxOut(std::string transactionId, int index, std::vector<UnspentTxOut>& aUnspentTxOuts) {
    for(int id = 0; id < int(aUnspentTxOuts.size()); id++) {
        if (aUnspentTxOuts[id].txOutId == transactionId && aUnspentTxOuts[id].txOutIndex == index)
            return std::make_pair(1, aUnspentTxOuts[id]);
    }
    return std::make_pair(0, UnspentTxOut("", 0, "", 0));
}

std::string getPublicKey(std::string aPrivateKey) {//TODO: MALO
        return "";//keyFromPrivate(aPrivateKey).getPublic(); //TODO: MALO
}

std::string Transaction::signTxIn(int txInIndex, std::string privateKey, std::vector<UnspentTxOut> aUnspentTxOuts) {
    TxIn txIn = txIns[txInIndex];
    std::string dataToSign = id;
    std::pair<bool, UnspentTxOut> tmp = findUnspentTxOut(txIn.txOutId, txIn.txOutIndex, aUnspentTxOuts);
    if (tmp.fi == 0)
        throw std::invalid_argument( "could not find referenced txOut\n" );
    UnspentTxOut referencedUnspentTxOut = tmp.se;
    std::string referencedAddress = referencedUnspentTxOut.address;

    if (getPublicKey(privateKey) != referencedAddress) {
        throw std::invalid_argument("trying to sign an input with private key that does not match the address that is referenced in txIn\n");
    }

    Keys key = Keys();//keyFromPrivate(privateKey); //TODO: MALO
    std::string signature = "";//toHexString(key.sign(dataToSign).toDER()); //TODO: Add ToHexString //MALO
    return signature;

}

UnspentTxOut::UnspentTxOut(std::string txOutId, int txOutIndex, std::string address, int amount) {
    this -> txOutId = txOutId;
    this -> txOutIndex = txOutIndex;
    this -> address = address;
    this -> amount = amount;
}

int TxIn::getTxInAmount(std::vector<UnspentTxOut> aUnspentTxOuts) {
    return findUnspentTxOut(txOutId, txOutIndex, aUnspentTxOuts).second.amount;
}

std::vector<UnspentTxOut> updateUnspentTxOuts(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts) {
    std::vector<UnspentTxOut> newUnspentTxOuts;
    for (int i = 0; i < int(aTransactions.size()); i++) {
        Transaction T = aTransactions[i];
        for (int j = 0; j < int(T.txOuts.size()); j++)
            newUnspentTxOuts.push_back(UnspentTxOut(T.id, j, T.txOuts[j].address, T.txOuts[j].amount));
    }

    std::vector<UnspentTxOut> consumedTxOuts;
    for (int i = 0; i < int(aTransactions.size()); i++) {
        Transaction T = aTransactions[i];
        for (int j = 0; j < int(T.txIns.size()); j++)
            consumedTxOuts.push_back(UnspentTxOut(T.txIns[j].txOutId, T.txIns[j].txOutIndex, "", 0));
    }

    //Removing the consumedTxOuts elements
    for (int i = 0; i < int(aUnspentTxOuts.size()); i++) {
        if (findUnspentTxOut(aUnspentTxOuts[i].txOutId, aUnspentTxOuts[i].txOutIndex, consumedTxOuts).first == 0)
            newUnspentTxOuts.push_back(aUnspentTxOuts[i]);
    }

    return newUnspentTxOuts;
}

bool isValidTxInStructure(TxIn txIn) {
    if ((&txIn) == nullptr) {
        std::cout << "txIn is null";
        return false;
    }
    else if (typeid(txIn.signature) != typeid("string")) {
        std::cout << "invalid signature type in txIn";
        return false;
    }
    else if (typeid(txIn.txOutId) != typeid("string")) {
        std::cout << "invalid txOutId type in txIn";
        return false;
    }
    else if (typeid(txIn.txOutIndex) != typeid(0)) {
        std::cout << "invalid txOutIndex type in txIn";
        return false;
    }
    else
        return true;
}

bool isValidTxInStructure(TxOut txIn) {
    if ((&txIn) == nullptr) {
        std::cout << "txIn is null";
        return false;
    }
    else if (typeid(txIn.address) != typeid("string")) {
        std::cout << "invalid signature type in txIn";
        return false;
    }
    else if (!isValidAddress(txIn.address)) {
        std::cout << "invalid txOutId type in txIn";
        return false;
    }
    else if (typeid(txIn.amount) != typeid(0)) {
        std::cout << "invalid txOutIndex type in txIn";
        return false;
    }
    else
        return true;
}

// valid address is a valid ecdsa public key in the 04 + X-coordinate + Y-coordinate format
bool isValidAddress(std::string address) {
    if (int(address.length()) == 130) {
        std::cout << address << "\n";
        std::cout << "invalid public key length\n";
        return false;
    }
    else if (!regex_match(address, std::regex("^[a-fA-F0-9]+$"))) {
        std::cout << "public key must contain only hex characters\n";
        return false;
    }
    else if (address.substr(0, 2) != "04") {
        std::cout << "public key must start with 04\n";
        return false;
    }
    return true;
}

bool isValidTxOutStructure(TxOut txOut) {
    if ((&txOut) == nullptr) {
        std::cout << "txOut is null";
        return false;
    }
    else if (typeid(txOut.address) != typeid("String")) {
        std::cout << "invalid address type in txOut";
        return false;
    }
    else if (!isValidAddress(txOut.address)) {
        std::cout << "invalid TxOut address";
        return false;
    }
    else if (typeid(txOut.amount) != typeid(0)) {
        std::cout << "invalid amount type in txOut";
        return false;
    }
    else
        return true;
}

bool Transaction::isValidTransactionStructure() {
    if (typeid(id) != typeid("string")) {
        std::cout << "transactionId missing";
        return false;
    }
    if (typeid(txIns) != typeid(std::vector<TxIn>())) {
        std::cout << "invalid txIns type in transaction";
        return false;
    }

    bool isValid = 1;
    for (int i = 0; i < int(txIns.size()); i++)
        isValid &= isValidTxInStructure(txIns[i]);

    if (!isValid) {
        std::cout << "invalid TxIns array";
        return false;
    }

    if (typeid(txOuts) != typeid(std::vector<TxOut>())) {
        std::cout << "invalid txOuts type in transaction";
        return false;
    }

    isValid = 1;
    for (int i = 0; i < int(txOuts.size()); i++)
        isValid &= isValidTxOutStructure(txOuts[i]);

    if (!isValid) {
        std::cout << "invalid TxOuts array";
        return false;
    }

    return true;
}

std::string TxIn::JSONStringify() {
    //TODO: Implement later
    return "";
}

bool validateTxIn(TxIn txIn, std::string id, std::vector<UnspentTxOut> aUnspentTxOuts) {
    std::pair<bool, UnspentTxOut> tmp = findUnspentTxOut(txIn.txOutId, txIn.txOutIndex, aUnspentTxOuts);
    if (tmp.first == 0) {
        std::cout << "referenced txOut not found: "; //<< TxIn.JSONStringify() << "\n";
        return false;
    }
    UnspentTxOut referencedUTxOut = tmp.second;
    std::string address = referencedUTxOut.address;

    Keys key = keyFromPublic(address); //TODO: MALO
    bool validSignature = 0;//key.verify(id, txIn.signature);
    if (!validSignature) {
        std::cout << "invalid txIn signature: " << txIn.signature << " txId: " << id << " address: " << address << "\n";
        return false;
    }
    return true;
}

bool hasDuplicates(std::vector<TxIn> txIns) {
    std::map<std::string, int> groups;
    int n = int(txIns.size());
    for (int i = 0; i < n; i++) {
        std::string elem = txIns[i].txOutId + std::to_string(txIns[i].txOutIndex);
        if (groups.count(elem))
            return 1;
        groups[elem] += 1;
    }
    return 0;
}

bool validateBlockTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex) {
    Transaction coinbaseTx = aTransactions[0];
    if (!coinbaseTx.validateCoinbaseTx(blockIndex)) {
        std::cout << "invalid coinbase transaction: "; //<< coinbaseTx.JSONStringify() << "\n";
        return 0;
    }

    //check for duplicate txIns. Each txIn can be included only once
    std::vector<TxIn> txIns;
    std::map<TxIn, bool> used;
    for (int i = 0; i < (int)(aTransactions.size()); i++) {
        for (int j = 0; j < (int)(aTransactions[i].txIns.size()); j++) {
            if (!used.count(aTransactions[i].txIns[j])) {
                txIns.push_back(aTransactions[i].txIns[j]);
                used[aTransactions[i].txIns[j]] = 1;
            }
        }
    }

    if (hasDuplicates(txIns))
        return 0;

    //all but coinbase transactions
    bool validate = 1;
    for (int i = 1; i < int(aTransactions.size()); i++)
        validate &= aTransactions[i].validateTransaction(aUnspentTxOuts);

    return validate;
}

bool Transaction::validateTransaction(std::vector<UnspentTxOut> aUnspentTxOuts) {
    if (!isValidTransactionStructure())
        return false;

    if (getTransactionId() != id) {
        std::cout << "Invalid tx id: " << id << "\n";
        return false;
    }

    bool hasValidTxIns = true;
    for (int i = 0; i < int(txIns.size()); i++)
        hasValidTxIns &= validateTxIn(txIns[i], id, aUnspentTxOuts);

    if (!hasValidTxIns) {
        std::cout << "some of the txIns are invalid in tx: " << id << "\n";
        return false;
    }

    int totalTxInValues = 0;
    for (int i = 0; i < int(txIns.size()); i++)
        totalTxInValues += txIns[i].getTxInAmount(aUnspentTxOuts);

    int totalTxOutValues = 0;
    for (int i = 0; i < int(txOuts.size()); i++)
        totalTxOutValues += txOuts[i].amount;

    if (totalTxInValues != totalTxOutValues) {
        std::cout << "totalTxOutValues != totalTxInValues in tx: " << id << "\n";
        return false;
    }

    return true;
}

bool Transaction::validateCoinbaseTx(int blockIndex) {
    if (getTransactionId() != id) {
        std::cout << "invalid coinbase tx id: " << id << "\n";
        return false;
    }
    if (int(txIns.size()) != 1) {
        std::cout << "one txIn must be specified in the coinbase transaction\n";
        return false;
    }
    if (txIns[0].txOutIndex != blockIndex) {
        std::cout << "the txIn index in coinbase tx must be the block height\n";
        return false;
    }
    if (int(txOuts.size()) != 1) {
        std::cout << "invalid number of txOuts in coinbase transaction\n";
        return false;
    }
    if (txOuts[0].amount != COINBASE_AMOUNT) {
        std::cout << "invalid coinbase amount in coinbase transaction\n";
        return false;
    }
    return true;
}

Transaction getCoinbaseTransaction(std::string address, int blockIndex) {
    Transaction t;
    TxIn txIn;
    txIn.signature = "";
    txIn.txOutId = "";
    txIn.txOutIndex = blockIndex;

    t.txIns = std::vector<TxIn>{txIn};
    t.txOuts = std::vector<TxOut>{TxOut(address, COINBASE_AMOUNT)};
    t.id = t.getTransactionId();
    return t;
}

