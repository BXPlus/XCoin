#include "transaction.h"
#include <stdexcept>
#include <regex>
#include <set>
#include <cstring>
/*
// Delete later zone
Keys::Keys(){

    EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);

    if(NULL == (key )){ //checks whether the EC_KEY was successfully created
        std::cout << "unsuccessful EC_KEY creation" << std::endl;
    }

    //generate the key pair
    if(1 != EC_KEY_generate_key(key)) {
        std::cout << " key generation problem" << std::endl;
    }

    // Set up private key in prv
    prv = EC_KEY_get0_private_key(key);
    if(!prv){
        std::cout << "Error getting private key" << std::endl;
    }
    //we get the hex form
    priv_key = BN_bn2hex(prv);


    // Set up public key in pub
    pub = EC_KEY_get0_public_key(key);
    if(!pub){
        std::cout << "Error getting public key" << std::endl;
    }
    //we set the hex form
    const EC_GROUP *group = NULL;
    group = EC_KEY_get0_group(key);
    BN_CTX *ctx;
    ctx = BN_CTX_new(); // ctx is an optional buffer to save time from allocating and deallocating memory whenever required
    pub_key = EC_POINT_point2hex(group, pub, POINT_CONVERSION_UNCOMPRESSED, ctx);


    EC_KEY_free(key); //we free the memory occupied by the useless 'key'
    BN_CTX_free(ctx);
}


Keys::Keys(std::string pubb){
    //We can't retrieve the private key from the public key
    prv = NULL;
    priv_key = NULL;

    const char* pub_key =pubb.c_str();
    EC_KEY *key;
    const EC_GROUP *group;
    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    group = EC_KEY_get0_group(key);
    BN_CTX *ctx;
    ctx = BN_CTX_new();

    pub = EC_POINT_hex2point(group, pub_key, NULL, ctx);
    pub_key = EC_POINT_point2hex(group, pub, POINT_CONVERSION_UNCOMPRESSED, ctx);

    EC_KEY_free(key); //we free the memory occupied by the useless 'key'
    BN_CTX_free(ctx);
}


Keys::Keys(EC_KEY *key){
    prv = EC_KEY_get0_private_key(key);
    if(!prv){
        std::cout << "Error getting private key" << std::endl;
    }
    //we get the hex form
    priv_key = BN_bn2hex(prv);

    // Set up public key in pub
    pub = EC_KEY_get0_public_key(key);
    //EC_KEY_set_public_key(key, pub);
    if(!pub){
        std::cout << "Error getting public key" << std::endl;
    }
    //we set the hex form
    EC_KEY *eckey = NULL;
    const EC_GROUP *group = NULL;
    eckey = EC_KEY_new_by_curve_name(NID_secp256k1);
    group = EC_KEY_get0_group(eckey);
    BN_CTX *ctx;
    ctx = BN_CTX_new(); // ctx is an optional buffer to save time from allocating and deallocating memory whenever required
    pub_key = EC_POINT_point2hex(group, pub, POINT_CONVERSION_UNCOMPRESSED, ctx);
}


Keys keyFromPrivate(std::string prv){
    //create the EC_KEY object
    EC_POINT *publ = NULL;
    EC_KEY *key;
    const EC_GROUP *group;
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    group = EC_KEY_get0_group(key);

    //Put the private key in a good form, derive the public key and assign them to the EC_KEY
    const char* priv_key = prv.c_str(); //converts from string to char
    BIGNUM *priv = NULL ;
    BN_hex2bn(&priv, priv_key); //the private key in BIGNUM form
    publ = EC_POINT_new(group);
    EC_POINT_mul(group, publ, priv, NULL, NULL, ctx);
    EC_KEY_set_private_key(key, priv);
    EC_KEY_set_public_key(key, publ);

    return  Keys(key);

};


Keys keyFromPublic(std::string adress) {
    return Keys(adress);
}


std::pair<uint8_t*, uint32_t> sign(std::string prv, std::string dataToSign){
    //convert from string to char
    const char *message = dataToSign.c_str();
    const char* priv_key = prv.c_str();

    //Create an EC_KEY object for signing
    EC_POINT *publ = NULL;
    EC_KEY *key;
    const EC_GROUP *group;
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    group = EC_KEY_get0_group(key);
    publ = EC_POINT_new(group);

    //Put the private key in a good form, derive the public key and assign them to the EC_KEY
    BIGNUM *priv = NULL ;
    BN_hex2bn(&priv, priv_key); //the private key in BIGNUM form
    EC_POINT_mul(group, publ, priv, NULL, NULL, ctx);
    EC_KEY_set_private_key(key, priv);
    EC_KEY_set_public_key(key, publ);


    //structure for the signature
    uint8_t *digest;
    uint8_t *signature;
    uint32_t signature_len;
    int ret_error;
    unsigned char   buffer_digest[SHA256_DIGEST_LENGTH];
    signature_len = ECDSA_size(key); // the signature size depends on the key

    signature     = (uint8_t *) OPENSSL_malloc(signature_len);
    digest        = SHA256((const unsigned char *)message, strlen(message), buffer_digest);


    ret_error     = ECDSA_sign(0, (const uint8_t *)digest, SHA256_DIGEST_LENGTH, signature, &signature_len, key);

    if (ret_error == 0){
        std::cout << "An error has occured when signing the data" << std::endl;
    }

    return std::pair<uint8_t*, uint32_t>(signature, signature_len);

}


bool verify(std::pair<uint8_t*, uint32_t> signature, std::string pub_key, std::string id) {
    const char *message = id.c_str();
    const char *pub = pub_key.c_str();

    //Create an EC_KEY object from our public key
    EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_GROUP *group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_POINT *public_key = EC_POINT_new(group);
    EC_KEY_generate_key(key);
    public_key = EC_POINT_hex2point(group, pub, public_key, nullptr);
    EC_KEY_set_public_key(key, public_key);

    //Clean the memory
    EC_GROUP_free(group);
    EC_POINT_free(public_key);

    unsigned char buffer_digest[SHA256_DIGEST_LENGTH];
    uint8_t *digest;
    digest = SHA256((const unsigned char *) message, strlen(message), buffer_digest);


    int verification = ECDSA_verify(0, digest, SHA256_DIGEST_LENGTH, signature.first, signature.second, key);
    if (verification == -1) { //if there is an error
        std::cout << "An error has occurred when computing the correctness of the signature" << std::endl;
        return 0;
    }

    return verification;
}
// Delete later zone
*/
const int COINBASE_AMOUNT = 50;


enum findUnspentTxOutOutcome {
    NotFoundUnspentTxOut = 0,
    FoundUnspentTxOut = 1
};


UnspentTxOut::UnspentTxOut() {
}


UnspentTxOut::UnspentTxOut(std::string txOutId, int txOutIndex, std::string address, int amount) {
    this -> txOutId = txOutId;
    this -> txOutIndex = txOutIndex;
    this -> address = address;
    this -> amount = amount;
}


TxOut::TxOut() {
}


TxOut::TxOut(std::string address, int amount) {
    this -> address = address;
    this -> amount = amount;
}


int TxIn::getTxInAmount(std::vector<UnspentTxOut> aUnspentTxOuts) {
    return findUnspentTxOut(txOutId, txOutIndex, aUnspentTxOuts).second.amount;
}


TxIn::TxIn() {
}


TxIn::TxIn(std::string txOutId, int txOutIndex, std::pair<uint8_t*, uint32_t> signature) {
    this -> txOutId = txOutId;
    this -> txOutIndex = txOutIndex;
    this -> signature = signature;
}


bool validateTxIn(TxIn txIn, std::string id, std::vector<UnspentTxOut> aUnspentTxOuts) {
    std::pair<bool, UnspentTxOut> tmp = findUnspentTxOut(txIn.txOutId, txIn.txOutIndex, aUnspentTxOuts);
    if (tmp.first == NotFoundUnspentTxOut) {
        std::cout << "referenced txOut not found";
        return false;
    }
    UnspentTxOut referencedUTxOut = tmp.second;
    std::string address = referencedUTxOut.address;

    bool validSignature = verify(txIn.signature, address, id);

    if (!validSignature) {
        std::cout << "invalid txIn signature: " << txIn.signature.first << " txId: " << id << " address: " << address << "\n";
        return false;
    }
    return true;
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


std::pair<uint8_t*, uint32_t> Transaction::signTxIn(int txInIndex, std::string privateKey, std::vector<UnspentTxOut> aUnspentTxOuts) {
    TxIn txIn = txIns[txInIndex];
    std::string dataToSign = id;
    std::pair<bool, UnspentTxOut> tmp = findUnspentTxOut(txIn.txOutId, txIn.txOutIndex, aUnspentTxOuts);
    if (tmp.first == NotFoundUnspentTxOut)
        throw std::invalid_argument( "could not find referenced txOut\n" );

    UnspentTxOut referencedUnspentTxOut = tmp.second;
    std::string referencedAddress = referencedUnspentTxOut.address;

    if (getPublicKey(privateKey) != referencedAddress)
        throw std::invalid_argument("trying to sign an input with private key that does not match the address that is referenced in txIn\n");

    std::pair<uint8_t*, uint32_t> signature = sign(privateKey, dataToSign);
    return signature;

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


Transaction::Transaction() {
}

Transaction::Transaction(std::vector<TxIn> txIns, std::vector<TxOut> txOuts, std::string id) {
    this->txIns = txIns;
    this->txOuts = txOuts;
    this->id = id;
}

std::pair<bool, UnspentTxOut> findUnspentTxOut(std::string transactionId, int index, std::vector<UnspentTxOut>& aUnspentTxOuts) {
    for(int id = 0; id < int(aUnspentTxOuts.size()); id++) {
        if (aUnspentTxOuts[id].txOutId == transactionId && aUnspentTxOuts[id].txOutIndex == index)
            return std::make_pair(FoundUnspentTxOut, aUnspentTxOuts[id]);
    }
    return std::make_pair(NotFoundUnspentTxOut, UnspentTxOut("", 0, "", 0));
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
        if (findUnspentTxOut(aUnspentTxOuts[i].txOutId, aUnspentTxOuts[i].txOutIndex, consumedTxOuts).first == NotFoundUnspentTxOut)
            newUnspentTxOuts.push_back(aUnspentTxOuts[i]);
    }

    return newUnspentTxOuts;
}


bool isValidTxInStructure(TxIn txIn) {
    if ((typeid(txIn.signature) != typeid(std::pair<uint8_t*, uint32_t>)) &&
            (typeid(txIn.signature.first) != typeid(uint8_t*)) &&
            (typeid(txIn.signature.second) !=typeid(uint32_t))) {
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


// valid address is a valid ecdsa public key in the 04 + X-coordinate + Y-coordinate format
bool isValidAddress(std::string address) {
    if (int(address.length()) != 130) {
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
    if (typeid(txOut.address) != typeid("String")) {
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


Transaction getCoinbaseTransaction(std::string address, int blockIndex) {
    Transaction t;
    TxIn txIn("", blockIndex, std::pair<uint8_t*, uint32_t>());

    t.txIns = std::vector<TxIn>{txIn};
    t.txOuts = std::vector<TxOut>{TxOut(address, COINBASE_AMOUNT)};
    t.id = t.getTransactionId();
    return t;
}


std::string getPublicKey(std::string aPrivateKey) {
    return keyFromPrivate(aPrivateKey).getPub();
}


bool hasDuplicates(std::vector<TxIn> txIns) {
    std::set<std::string> groups;
    int n = int(txIns.size());
    for (int i = 0; i < n; i++) {
        std::string elem = txIns[i].txOutId + std::to_string(txIns[i].txOutIndex);
        if (groups.find(elem) != groups.end())
            return 1;
        groups.insert(elem);
    }
    return 0;
}


bool validateBlockTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex) {
    Transaction coinbaseTx = aTransactions[0];
    if (!coinbaseTx.validateCoinbaseTx(blockIndex)) {
        std::cout << "invalid coinbase transaction";
        return 0;
    }

    //check for duplicate txIns. Each txIn can be included only once
    std::vector<TxIn> txIns;
    std::set<TxIn> used;
    for (int i = 0; i < (int)(aTransactions.size()); i++) {
        for (int j = 0; j < (int)(aTransactions[i].txIns.size()); j++) {
            if (used.find(aTransactions[i].txIns[j]) != used.end()) {
                txIns.push_back(aTransactions[i].txIns[j]);
                used.insert(aTransactions[i].txIns[j]);
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


std::vector<UnspentTxOut> processTransactions(std::vector<Transaction> aTransactions, std::vector<UnspentTxOut> aUnspentTxOuts, int blockIndex) {
    if (!validateBlockTransactions(aTransactions, aUnspentTxOuts, blockIndex)) {
        std::cout << "invalid block transactions";
        return std::vector<UnspentTxOut>();
    }
    return updateUnspentTxOuts(aTransactions, aUnspentTxOuts);
}
