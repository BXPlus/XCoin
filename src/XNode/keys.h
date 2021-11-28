
// Created by Malo Lahogue on 14/11/2021.
//

#ifndef XCOIN_KEYS_H
#define XCOIN_KEYS_H
//#include "transaction.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>

class Keys {
public:
    Keys(); //constructor which creates the private and public key
    Keys(std::string pubb); //constructor which creates the private and public key


    char const* keyFromPrivate(std::string priv_keyy, std::string form);//return the public key from the private one
//    bool verify(string id, string txOutId, int txOutIndex, string signature, vector<UnspentTxOut> aUnspentTxOuts);

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
Keys keyFromPublic(std::string address, std::string form); //returns a key whose public key is adress
#endif //XCOIN_KEYS_H

//ECDSA_SIG()