
// Created by Malo Lahogue on 14/11/2021.
//

#ifndef XCOIN_KEYS_H
#define XCOIN_KEYS_H
//#include "transaction.h"
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include "openssl/sha.h"

class Keys {
public:
    Keys(); //constructor which creates the private and public key randomly
    Keys(std::string pubb); //constructor which creates a key from a public key
    Keys(EC_KEY *key); //constructor from an EC_KEY object


    char const* getPriv(){
        //returns the hexadecimal fom of the private key
        return priv_key;
    }
    char const* getPub(){
        //returns the hexadecimal fom of the public key
        return pub_key;
    }

private:
    BIGNUM const* prv;        //private key (which is a big integer)
    char const* priv_key;         //private key in hexadecimal form
    EC_POINT const* pub;      //public key which is a point made of two coordinates and depending on the private key
    char const* pub_key;         //public key in hexadecimal form

};

    //FREE FUNCTIONS

Keys keyFromPrivate(std::string priv_keyy);
    //return a key from a private key

Keys keyFromPublic(std::string address);
    //returns a key whose public key is address

std::pair<uint8_t*, uint32_t> sign(std::string priv_key, std::string dataToSign);
    /*
     * Computes the signature of a given data with a given private key:
     *      INPUTS:
     *          - pkey : a private key
     *          - dataToSign : the data we want to make a signature of
     *
     *      OUTPUTS:
     *          a pair of data:
     *          -first (array of uint8_t) is the signature
     *          - Second is the length of the signature
     */

bool verify(std::pair<uint8_t*, uint32_t> signature, std::string pub_key, std::string id);
    /*
     * Verifies whether the signature has been signed by a given public key
     *      INPUTS:
     *          - a pair of <Signature, signature_length>
     *          - a public key
     *          - id : the data which has been signed
     *      OUTPUTS:
     *          - 0 if the data hasn't been signed by this public key or if it is not the data which has been signed
     *          - 1 if everything is correct
     */

#endif //XCOIN_KEYS_H