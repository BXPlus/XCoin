//
// Created by Malo Lahogue on 14/11/2021.
//
//for key generation, we will use the ECDSA which is also used by bitcoin btw.
//It offers a more secure mechanism than RSA

#include "keys.h"

Keys::Keys(){

    EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);

    if(NULL == (key )){ //checks wether the EC_KEY (elliptical curve key object wes succesfully created) was succefully created
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

    EC_KEY_free(key); //we free the memory occupied by the useless 'key'
    BN_CTX_free(ctx);

}

Keys::Keys(std::string pubb){
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


Keys keyFromPrivate(std::string priv_keyy){
    const char* priv_key = priv_keyy.c_str(); //converts from string to char
    BIGNUM *priv = NULL ;
    BN_hex2bn(&priv, priv_key); //the private key in BIGNUM form

    EC_POINT *publ = NULL;
    EC_KEY *key;
    const EC_GROUP *group;
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    group = EC_KEY_get0_group(key);
    publ = EC_POINT_new(group);
    EC_POINT_mul(group, publ, priv, NULL, NULL, ctx);

    EC_KEY_set_private_key(key, priv);
    EC_KEY_set_public_key(key, publ);

    return  Keys(key);

};



Keys keyFromPublic(std::string adress) {
    Keys key = Keys(adress);

    return key;
}


std::string sign(std::string prv, std::string dataToSign){
    const char *message = dataToSign.c_str();

    const char* priv_key = prv.c_str(); //converts from string to char
    BIGNUM *priv = NULL ;
    BN_hex2bn(&priv, priv_key); //the private key in BIGNUM form

    EC_POINT *publ = NULL;
    EC_KEY *key;
    const EC_GROUP *group;
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    group = EC_KEY_get0_group(key);
    publ = EC_POINT_new(group);
    EC_POINT_mul(group, publ, priv, NULL, NULL, ctx);

    EC_KEY_set_private_key(key, priv);
    EC_KEY_set_public_key(key, publ);

    uint8_t *digest;
    uint8_t *signature;
    uint32_t signature_len;
    int ret_error;
    unsigned char   buffer_digest[SHA256_DIGEST_LENGTH];

    signature_len = ECDSA_size(key); // the signature size depends on the key

    signature     = (uint8_t *) OPENSSL_malloc(signature_len);
    digest        = SHA256((const unsigned char *)message, strlen(message), buffer_digest);
    ret_error     = ECDSA_sign(0, (const uint8_t *)digest, SHA256_DIGEST_LENGTH, signature, &signature_len, key);

    static char hex[] = "0123456789ABCDEF";
    std::string sgn = "";
    for (size_t i = 0; i < signature_len; i++)
    {
        sgn = sgn + hex[((signature[i] & 0xF0) >> 4)];
        sgn = sgn + hex[((signature[i] & 0x0F) >> 0)];

    }
    return sgn;

}


//Uncomment when ready
/*


bool Keys::verify(string id, string txOutId, int txOutIndex, string signature, vector<UnspentTxOut> aUnspentTxOuts){
//We will create the signature which should be signing this TxIn and compare it to the one we have
//We use an addapted version of signTxIn

string sign2;


string dataToSign = id;

vector<bool, UnspentTxOut> tmp = findUnspentTxOut(txOutId, txOutIndex, aUnspentTxOuts);
if (tmp.fi == 0)
    throw invalid_argument( "could not find referenced txOut\n" );
string referencedUnspentTxOut = tmp.se;
string referencedAddress = referencedUnspentTxOut.address;

if (pub_key != referencedAddress) {
    throw invalid_argument('trying to sign an input with private' +
                           ' key that does not match the address that is referenced in txIn\n');
}

sign2 = toHexString(sign(dataToSign).toDER()); //TODO: Add ToHexString



    if (signature != sign2){
        return false
    }

    return true


}*/