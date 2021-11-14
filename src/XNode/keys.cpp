//
// Created by Malo Lahogue on 14/11/2021.
//
//for key generation, we will use the ECDSA which is also used by bitcoin btw.
//It offers a more secure mechanism than RSA


#include "keys.h"
#include <openssl/obj_mac.h>
#include <openssl/ec.h> //the elliptic curve library from openSSL


keys::key(){
    //generate the private and public key
    EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);

    if(NULL == (key ))
        handleErrors();

}