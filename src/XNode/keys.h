
// Created by Malo Lahogue on 14/11/2021.
//

#ifndef XCOIN_KEYS_H
#define XCOIN_KEYS_H
#include <iostream>
#include <openssl/obj_mac.h>
#include <openssl/ec.h> //the elliptic curve library from openSSL

class Keys {
public:
    Keys(); //constructor which creates the private and public key

    BIGNUM const* prv;        //private key (which is a big integer)
    char const* priv_key;         //private key in hexadecimal form
    EC_POINT const* pub;      //public key which is a point made of two coordinates and depending on the private key
    char const* pub_key;         //public key in hexadecimal form


};

#endif //XCOIN_KEYS_H