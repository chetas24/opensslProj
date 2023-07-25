#include <iostream>
#include <openssl/rand.h>
#include <cstring>


std::string generateRandomPassword(int length) {
    const std::string valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$";

    unsigned char buffer[length];
    std::string password;

    // Generate random bytes
    if (RAND_bytes(buffer, sizeof(buffer)) != 1) {
        std::cerr << "Error generating random numbers." << std::endl;
        return password;
    }

    // Convert random bytes to password characters
    // if the valid_char is 66
    // random byte from buffer example 150
    // therefore 150 % 66 = 18
    // 18 = r, then r is appended to password
    for (int i = 0; i < length; ++i) {
        unsigned char randomChar = buffer[i] % valid_chars.length();
        password += valid_chars[randomChar];
    }

    return password;
}

int main() {
    int passwdLength = 10;

    std::string password = generateRandomPassword(passwdLength);
    std::cout << "Generated Random Password: " << password << std::endl;

    return 0;
}
