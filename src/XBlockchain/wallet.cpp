#include "transaction.h"


//# Generate and store the private Key

string generatePrivateKey()
{
    return ""; //To implement using key
}

string getPrivateFromWallet()
{
    return "";
}

string getPublicFromWallet()
{
    string privateKey = getPrivateFromWallet();
    string key; //add when implemented in transaction
    return ""; //Public key in the keyPair encoded.
}

//# Wallet Balance

void initWallet() {
    return;
}

void deleteWallet() {
    return;
}



string getBalance()
{
    return "";
}




void createTxOuts(string receiverAddress, string myAddress, int amount, int leftOverAmount) {
//    TxOut txOut1 = new TxOut(receiverAddress, amount);
//    if (leftOverAmount === 0) {
//        return [txOut1]
//    } else {
//        TxOut leftOverTx = new TxOut(myAddress, leftOverAmount);
//        return [txOut1, leftOverTx];
    return;
}
