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
    //EC_KEY_set_private_key(key, prv);
    if(!prv){
        std::cout << "Error getting private key" << std::endl;
    }
    char *priv_key = BN_bn2hex(prv);

    std::cout << prv << "      " << priv_key << std::endl;


    // Set up public key in pub
    pub = EC_KEY_get0_public_key(key);
    //EC_KEY_set_public_key(key, pub);
    if(!pub){
        std::cout << "Error getting public key" << std::endl;
    }
    EC_KEY *eckey = NULL;
    const EC_GROUP *group = NULL;
    eckey = EC_KEY_new_by_curve_name(NID_secp256k1);
    group = EC_KEY_get0_group(eckey);
    BN_CTX *ctx;
    ctx = BN_CTX_new(); // ctx is an optional buffer to save time from allocating and deallocating memory whenever required
    char *pub_key = EC_POINT_point2hex(group, pub, POINT_CONVERSION_UNCOMPRESSED, ctx);

    std::cout << pub << "      " << pub_key << std::endl;

    /*
    BIGNUM *priv_key;
    EC_GROUP *group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_KEY *key = EC_KEY_new();
    EC_POINT *pub_key = EC_POINT_new(group);

    EC_KEY_set_group(key, group);
    EC_KEY_set_private_key(key, priv_key);
    EC_POINT_mul(group, pub_key, priv_key, NULL, NULL, NULL);
    EC_KEY_set_public_key(key, pub_key);

    prv = priv_key;
    pub = pub_key;

    std::cout << priv_key << std::endl;
*/

    //EC_KEY_free(key);
}