//
// Created by Malo Lahogue on 14/11/2021.
//

#ifndef XCOIN_KEYS_H
#define XCOIN_KEYS_H


class keys {
public:
    keys(); //constructor which creates the private and public key

    BIGNUM *prv;        //private key (which is a big integer)
    EC_POINT *pub;      //public key which is a point made of two coordinates and depending on the private key
};

#endif //XCOIN_KEYS_H
