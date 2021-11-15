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
}