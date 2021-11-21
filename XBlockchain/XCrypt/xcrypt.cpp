//
// Created by ZAINANA Salma on 18/11/2021.
//
#include <iostream>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv,
            unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    /* initializing ctx
     */
    if (!)


}


void handleErrors(void){
/*ERR_print_errors() is a convenience function that prints the error strings for all errors that OpenSSL has recorded to bp, thus emptying the error queue.*/
 ERR_rint_errors_fp(stderr)
 /*stderr standard error*/
 abort();
}

int main(void) {
    /* we want to establish the key and the iv.
     * /

     /* 128 bit iv.
     */
    unsigned char *iv=  ;
    unsigned char *key= ;

    unsigned char *plaintext;

    /* pour stocker le ciphertext*/
    unsigned char ciphertext[128];

    /*pour stocker le text decrypter*/
    unsigned char decryptedtext[128];

    int decryptedtext_len;

    int ciphertext_len;

    /* Encrypt the plaintext */
    ciphertext_len = encrypt(plaintext, strlen((char *) plaintext), key, iv, ciphertext);
    std::cout << " code is : " << (const char *) ciphertext << ;

    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

    /*NULL terminator*/
    decryptedtext[decryptedtext_len] = '\0';

    std::cout << " Decrypted text is : " << decryptedtext << ;
};
