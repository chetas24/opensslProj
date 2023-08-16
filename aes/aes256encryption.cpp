#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>

const int KEY_SIZE = 32;  // AES-256
const int IV_SIZE = 16;   // 128-bit IV

void handleErrors() {
    std::cerr << "An error occurred.\n";
    exit(1);
}

void encryptAndDecrypt() {
    // Generate a random encryption key and IV
    unsigned char key[KEY_SIZE];
    unsigned char iv[IV_SIZE];
    if (RAND_bytes(key, KEY_SIZE) != 1 || RAND_bytes(iv, IV_SIZE) != 1) {
        handleErrors();
    }

    // Plaintext message
    const char *plaintext = "Hello, OpenSSL AES!";
    int plaintextLength = strlen(plaintext);

    // Buffer for ciphertext and decrypted text
    unsigned char ciphertext[1024];
    unsigned char decryptedtext[1024];
    int ciphertextLength, decryptedtextLength;

    // Initialize the encryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        handleErrors();
    }

    // Initialize the encryption operation
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv) != 1) {
        handleErrors();
    }

    // Encrypt the plaintext
    if (EVP_EncryptUpdate(ctx, ciphertext, &ciphertextLength, (const unsigned char *)plaintext, plaintextLength) != 1) {
        handleErrors();
    }

    // Finalize the encryption
    if (EVP_EncryptFinal_ex(ctx, ciphertext + ciphertextLength, &ciphertextLength) != 1) {
        handleErrors();
    }
    ciphertextLength += ciphertextLength;

    // Print ciphertext
    std::cout << "Ciphertext:\n";
    for (int i = 0; i < ciphertextLength; i++) {
        printf("%02x", ciphertext[i]);
    }
    std::cout << std::endl;

    // Initialize the decryption context
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv) != 1) {
        handleErrors();
    }

    // Decrypt the ciphertext
    if (EVP_DecryptUpdate(ctx, decryptedtext, &decryptedtextLength, ciphertext, ciphertextLength) != 1) {
        handleErrors();
    }

    // Finalize the decryption
    if (EVP_DecryptFinal_ex(ctx, decryptedtext + decryptedtextLength, &decryptedtextLength) != 1) {
        handleErrors();
    }
    decryptedtextLength += decryptedtextLength;

    // Null-terminate the decrypted text
    decryptedtext[decryptedtextLength] = '\0';

    // Print decrypted text
    std::cout << "Decrypted Text: " << decryptedtext << std::endl;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();

    // Seed the random number generator
    RAND_load_file("/dev/urandom", 32);

    // Perform encryption and decryption
    encryptAndDecrypt();

    // Clean up OpenSSL
    EVP_cleanup();

    return 0;
}
