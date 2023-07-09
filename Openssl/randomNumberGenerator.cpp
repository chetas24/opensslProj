#include <iostream>
#include <openssl/rand.h>
#include <cstring>

int main() {
    unsigned char buffer[4];  // Buffer to store the random bytes

    // This function helps ensure that the random number generator is sufficiently seeded with entropy, making the generated random numbers more secure.
    RAND_poll();

    // Generate 4 random bytes
    // RAND_bytes generates random bytes and stores in buffer
    if (RAND_bytes(buffer, sizeof(buffer)) != 1) {
        std::cerr << "Error generating random numbers." << std::endl;
        return 1;
    }

    // Convert the random bytes to an integer
    unsigned int randomNum;
    memcpy(&randomNum, buffer, sizeof(randomNum));
    // memcpy(destination, source, size): it copies from source to destination
    // sizeof(randomNum) specifies that number of bytes should be copied from source(buffer) to destination(randomNum)

    std::cout << "Random Number: " << randomNum << std::endl;

    return 0;
}
