//
// Created by Malo Lahogue on 14/11/2021.
//
//for key generation, we will use the ECDSA which is also used by bitcoin btw.
//It offers a more secure mechanism than RSA


#include "keys.h"
#include <openssl/obj_mac.h>
#include <openssl/ec.h> //the elliptic curve library from openSSL


keys::key(){
    EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);

    if(NULL == (key )) //checks wether the EC_KEY (elliptical curve key object wes succesfully created)
        handleErrors();

    //generate the key pair
    if(1 != EC_KEY_generate_key(key)) handleErrors();

    // Set up private key in prv
    if(1 != EC_KEY_set_private_key(key, prv)) handleErrors();

    // Set up public key in pub
    if(1 != EC_KEY_set_public_key(key, pub)) handleErrors();
}