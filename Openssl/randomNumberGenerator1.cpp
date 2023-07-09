#include <iostream>
#include <openssl/rand.h>
#include <cstring>

int main() {
    const int NUM_RANDOM_NUMBERS = 7;
    
    unsigned char buffer[sizeof(unsigned int)];
    
    RAND_poll();

    // Generating multiple random numbers
    for (int i = 0; i < NUM_RANDOM_NUMBERS; i++) {
        if (RAND_bytes(buffer, sizeof(buffer)) != 1) {
            std::cerr << "Error generating random numbers....." << std::endl;
            return 1;
        }

        // Convert the random bytes to an unsigned int
        unsigned int randomNum;
        memcpy(&randomNum, buffer, sizeof(randomNum));
        // memcpy is the copy function to copy buffer to randomNum

        std::cout << "Random Number " << i + 1 << ": " << randomNum << std::endl;
    }

    return 0;
}
