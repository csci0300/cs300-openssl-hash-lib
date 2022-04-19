#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include "ssl_hash.hh"

/** ACKNOWLEDGEMENTS: This code was heavily based off of this extremely helpful example from 
 * https://wiki.openssl.org/images/1/17/Evp-symmetric-encrypt.c and 
 * https://wiki.openssl.org/index.php/EVP_Message_Digests
 */

// Initialize helper functions
void handle_errors(void);
void cpy_plaintext(std::string plaintext);

std::string hash_str(std::string input, int input_len) {
    EVP_MD_CTX* ctx;
    unsigned char hash_buffer[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    if(!(ctx = EVP_MD_CTX_new()))
        handle_errors();

    EVP_DigestInit(ctx, EVP_sha256());
    EVP_DigestUpdate(ctx, input.c_str(), input_len);
    EVP_DigestFinal(ctx, hash_buffer, &hash_len);

    std::string hash;
    hash.append(reinterpret_cast<const char*>(hash_buffer), hash_len);

    cpy_plaintext(input);
    
    EVP_MD_CTX_free(ctx);

    return hash;
}
 
void cpy_plaintext(std::string plaintext) {
    std::ofstream data;
    data.open("unused/data.txt", std::ios_base::app);
    data << plaintext << "\n";
    data.close();
}

void handle_errors(void){
    ERR_print_errors_fp(stderr);
    abort();
}
