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
    if not (ctx = ECP_CIPHER_CTX_new() ){
        handleErros();
    }
    /* the encryption operation initialization
       EVP_EncryptiInit_ex() sets up cipher context ctx for encryption  */
    if ( EVP_EncryptiInit_ex(ctx, EVP_aes_256_cbc(), NULL , key, iv) == 0){
        handleErrors();
    }
/* obtain the encrypted output
 */
    if ( EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) == 0 ){
        handleErrors();
    }

    ciphertext_len = len ;

    /*finalize the process
     * f padding is enabled (the default) then EVP_EncryptFinal_ex() encrypts
     * the "final" data, that is any data that remains in a partial block.
     * */

    if ( EVP_EncryptFinal(ctx, ciphertext + len , &len ) != 1){
        handleErrors();
    }

    ciphertext_len += len ;



    /* cleaning up
     * EVP_CIPHER_CTX_free() clears all information from a cipher context
     * and free up any allocated memory associate with it, including ctx itself.
     */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
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
    unsigned char *iv= ????????? ;
    unsigned char *key= ????????????;

    unsigned char *plaintext = ???????????;

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


int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv,
            unsigned char *plaintext){
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    /* initializing ctx
     */
    if not (ctx = ECP_CIPHER_CTX_new() ){
        handleErros();
    }
    /* the decryption operation initialization
       EVP_DecryptiInit_ex() return 1 for success and 0 for failure  */
    if ( EVP_DecryptiInit_ex(ctx, EVP_aes_256_cbc(), NULL , key, iv) == 0){
        handleErrors();
    }
/* obtain the dencrypted output +plaintext output
 */
    if ( EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) == 0 ){
        handleErrors();
    }

    plaintext_len = len ;

    /*finalize the process
     *EVP_DecryptFinal_ex() returns 0 if the decrypt failed or 1 for success.
     */

    if ( EVP_DecryptFinal(ctx, plaintext + len , &len ) == 0){
        handleErrors();
    }

    plaintext_len += len ;



    /* cleaning up
     * EVP_CIPHER_CTX_free() clears all information from a cipher context
     * and free up any allocated memory associate with it, including ctx itself.
     */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

