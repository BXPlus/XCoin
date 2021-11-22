//
// Created by youssef on 11/8/21.
//

#include "transaction.h"
#include "XNode/keys.h"
#include <regex.h>
#include <stdexcept>

const int COINBASE_AMOUNT = 50;

TxOut::TxOut(string address, int amount) {
    this -> address = address;
    this -> amount = amount;
}

string Transaction::getTransactionId() {
    stringstream txInsContent;
    for (int i = 0; i < int(txIns.size()); i++) {
        element = txIns[i];
        txInsContent << element.txOutId << string(element.txOutIndex);
    }
    stringstream txOutsContent;
    for (int i = 0; i < int(txOuts.size()); i++) {
        element = txOuts[i];
        txOutsContent << element.address << element.amount;
    }
    return sha256(txInsContent.str() + txOutsContent.str());
}

string getPublicKey(string aPrivateKey) {
    return keyFromPrivate(aPrivateKey, 'hex').getPublic().encode('hex');
}

string Transaction::signTxIn(int txInIndex, string privateKey, vector<UnspentTxOut> aUnspentTxOuts) {
    TxIn txIn = txIns[txInIndex];
    string dataToSign = id;
    vector<bool, UnspentTxOut> tmp = findUnspentTxOut(txIn.txOutId, txIn.txOutIndex, aUnspentTxOuts);
    if (tmp.fi == 0)
        throw invalid_argument( "could not find referenced txOut\n" );
    string referencedUnspentTxOut = tmp.se;
    string referencedAddress = referencedUnspentTxOut.address;

    if (getPublicKey(privateKey) != referencedAddress) {
        throw invalid_argument('trying to sign an input with private' +
                    ' key that does not match the address that is referenced in txIn\n');
    }

    Keys key = keyFromPrivate(privateKey, 'hex');
    string signature = toHexString(key.sign(dataToSign).toDER()); //TODO: Add ToHexString

    return signature;

}

UnspentTxOut::UnspentTxOut(string txOutID, int txOutIndex, string address, int amount) {
    this -> txOutID = txOutID;
    this -> txOutIndex = txOutIndex;
    this -> address = address;
    this -> amount = amount;
}

pair<bool, UnspentTxOut> findUnspentTxOut(string transactionId, int index, vector<UnspentTxOut>& aUnspentTxOuts) {
    for (int id = 0; id < int(aUnspentTxOuts.size()); id++) {
        if (aUnspentTxOuts[id].txOutId == transactionId && aUnspentTxOuts[id].txOutIndex == index)
            return make_pair(1, aUnspentTxOuts[id]);
    }
    return make_pair(0, UnspentTxOut("", 0, "", 0));
}

int TxIn::getTxInAmount(vector<UnspentTxOut> aUnspentTxOuts) {
    return findUnspentTxOut(txOutId, txOutIndex, aUnspentTxOuts).second.amount;
}

vector<UnspentTxOut> updateUnspentTxOuts(vector<Transaction> aTransactions, vector<UnspentTxOut> aUnspentTxOuts) {
    vector<UnspentTxOut> newUnspentTxOuts;
    for (int i = 0; i < int(aTransactions.size()); i++) {
        Transaction T = aTransactions[i];
        for (int j = 0; j < int(T.txOuts.size()); j++)
            newUnspentTxOuts.push_back(UnspentTxOut(T.id, j, T.txOuts[j].address, T.txOuts[j].amount);
    }

    vector<UnspentTxOut> consumedTxOuts;
    for (int i = 0; i < int(aTransactions.size()); i++) {
        Transaction T = aTransactions[i];
        for (int j = 0; j < int(T.txIns.size()); j++)
            consumedTxOuts.push_back(UnspentTxOut(T.txIns_array[j].txOutId, T.txIns_array[j].txOutIndex, "", 0);
    }

    //Removing the consumedTxOuts elements
    for (int i = 0; i < int(aUnspentTxOuts.size()); i++) {
        if (findUnspentTxOut(aUnspentTxOuts[i].txOutId, aUnspentTxOuts[i].txOutIndex, consumedTxOuts).first == 0)
            newUnspentTxOuts.push_back(aUnspentTxOuts[i]);
    }

    return newUnspentTxOuts;
}

bool isValidTxInStructure(TxIn txIn) {
    if ((*txIn) == nullptr) {
        cout << "txIn is null";
        return false;
    }
    else if (typeid(txIn.signature) != typeid("string")) {
        cout << "invalid signature type in txIn";
        return false;
    }
    else if (typeid(txIn.txOutId) != typeid("string")) {
        cout << "invalid txOutId type in txIn";
        return false;
    }
    else if (typeid(txIn.txOutIndex) !== typeid(0)) {
        cout << "invalid txOutIndex type in txIn";
        return false;
    }
    else
        return true;
}

bool isValidTxOutStructure(TxOut txOut) {
    if ((*txOut) == nullptr) {
        cout << "txIn is null";
        return false;
    }
    else if (typeid(txOut.address) != typeid("string")) {
        cout << "invalid signature type in txIn";
        return false;
    }
    else if (!isValidAddress(txOut.address)) {
        cout << "invalid txOutId type in txIn";
        return false;
    }
    else if (typeid(txOut.amount) != typeid(0)) {
        cout << "invalid txOutIndex type in txIn";
        return false;
    }
    else
        return true;
}

// valid address is a valid ecdsa public key in the 04 + X-coordinate + Y-coordinate format
bool isValidAddress(string address) {
    if (int(address.length()) == 130) {
        cout << address << "\n";
        cout << "invalid public key length\n";
        return false;
    }
    else if (!regex_match(address, regex("^[a-fA-F0-9]+$"))) {
        cout << "public key must contain only hex characters\n";
        return false;
    }
    else if (address.substr(0, 2) != "04") {
        cout << "public key must start with 04\n";
        return false;
    }
    return true;
}

bool isValidTxOutStructure(TxOut txOut) {
    if ((*txOut) == nullptr) {
        cout << "txOut is null";
        return false;
    }
    else if (typeid(txOut.address) != typeid("String")) {
        cout << "invalid address type in txOut";
        return false;
    }
    else if (!isValidAddress(txOut.address)) {
        cout << "invalid TxOut address";
        return false;
    }
    else if (typeid(txOut.amount) != typeid(0)) {
        cout << "invalid amount type in txOut";
        return false;
    }
    else
        return true;
}

bool Transaction::isValidTransactionStructure() {
    if (typeid(id) != typeid("string")) {
        cout << "transactionId missing";
        return false;
    }

    if (typeid(txIns) != typeid(vector<TxIn>())) {
        cout << "invalid txIns type in transaction";
        return false;
    }

    bool isValid = 1;
    for (int i = 0; i < int(txIns.size()); i++)
        isValid &= isValidTxInStructure(txIns[i]);

    if (!isValid) {
        cout << "invalid TxIns array";
        return false;
    }

    if (typeid(txOuts) != typeid(vector<TxOut>())) {
        cout << "invalid txOuts type in transaction";
        return false;
    }

    isValid = 1;
    for (int i = 0; i < int(txOuts.size()); i++)
        isValid &= isValidTxOutStructure(txOuts[i]);

    if (!isValid) {
        cout << "invalid TxOuts array";
        return false;
    }

    return true;
}

string TxIn::JSONStringify() {
    //TODO: Implement later
    return "";
}

bool TxIn::validateTxIn(string id, vector<UnspentTxOut> aUnspentTxOuts) {
    pair<bool, UnspentTxOut> tmp = findUnspentTxOut(txOutId, txOutIndex, aUnspentTxOuts);
    if (tmp.first == 0) {
        cout << "referenced txOut not found: " << JSONStringify() << "\n";
        return false;
    }
    string referencedUTxOut = tmp.second;
    string address = referencedUTxOut;

    Keys key = keyFromPublic(address, "hex");
    bool validSignature = key.verify(id, signature);
    if (!validSignature) {
        cout << "invalid txIn signature: " << signature << " txId: " << id << " address: " << address << "\n";
        return false;
    }
    return true;
}

bool Transaction::validateTransaction(vector<UnspentTxOut> aUnspentTxOuts) {
    if (!isValidTxOutStructure())
        return false;

    if (getTransactionId() != id) {
        cout << "Invalid tx id: " << id << "\n";
        return false;
    }

    bool hasValidTxIns = true;
    for (int i = 0; i < int(txIns.size()); i++)
        hasValidTxIns &= txIns[i].validateTxIn(id, aUnspentTxOuts);

    if (!hasValidTxIns) {
        cout << "some of the txIns are invalid in tx: " << id << "\n";
        return false;
    }

    int totalTxInValues = 0;
    for (int i = 0; i < int(txIns.size()); i++)
        totalTxInValues += txIns[i].getTxInAmount(aUnspentTxOuts);

    int totalTxOutValues = 0;
    for (int i = 0; i < int(txOuts.size()); i++)
        totalTxOutValues += txOuts[i].amount;

    if (totalTxInValues != totalTxOutValues) {
        cout << "totalTxOutValues != totalTxInValues in tx: " << id << "\n";
        return false;
    }

    return true;
}

bool Transaction::validateCoinbaseTx(int blockIndex) {
    if (getTransactionId() != id) {
        cout << "invalid coinbase tx id: " << id << "\n";
        return false;
    }
    if (int(txIns.size()) != 1) {
        cout << "one txIn must be specified in the coinbase transaction\n";
        return false;
    }
    if (txIns[0].txOutIndex != blockIndex) {
        cout << "the txIn index in coinbase tx must be the block height\n";
        return false;
    }
    if (int(txOut.size()) != 1) {
        cout << "invalid number of txOuts in coinbase transaction\n";
        return false;
    }
    if (txOuts[0].amount != COINBASE_AMOUNT) {
        cout << "invalid coinbase amount in coinbase transaction\n";
        return false;
    }
    return true;
}

Transaction getCoinbaseTransaction(string address, int blockIndex) {
    Transaction t();
    TxIn txIn();
    txIn.signature = "";
    txIn.txOutId = "";
    txIn.txOutIndex = blockIndex;

    t.txIns = vector<TxIn>{txIn};
    t.txOuts = vector<TxOut>{TxOut(address, COINBASE_AMOUNT)};
    t.id = t.getTransactionId();
    return t;
}