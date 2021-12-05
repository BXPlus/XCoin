//
// Created by Malo Lahogue on 14/11/2021.
//
//for key generation, we will use the ECDSA which is also used by bitcoin btw.
//It offers a more secure mechanism than RSA

#include "keys.h"

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

    return std::pair(signature, signature_len);

}


bool verify(std::pair<uint8_t*, uint32_t> signature, std::string pub_key, std::string id){
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

    unsigned char   buffer_digest[SHA256_DIGEST_LENGTH];
    uint8_t *digest;
    digest = SHA256((const unsigned char *)message, strlen(message), buffer_digest);


    int verification = ECDSA_verify(0, digest, SHA256_DIGEST_LENGTH, signature.first, signature.second, key);

    if (verification == -1){ //if there is an error
        std::cout << "An error has occurred when computing the correctness of the signature" << std::endl;
        return 0;
    }

    return verification;
}