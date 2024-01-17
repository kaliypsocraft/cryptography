#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "cryptography.h"
#include "constants.h"
#include "sort.h"
#include "matrices.h"
#include "string_util.h"

using std::vector, std::cout, std::cin, std::find;

const int LIMIT = 50;

// Function prototypes
void getUserInput(std::string& message, std::string& protocol);
void processProtocol(const std::string& protocol, const std::string& message);

int main() {
    cout << "[ Welcome to Kali's Cryptology Project ]" << std::endl;
    
    std::string message;
    std::string protocol;

    int iterations = 0;
    
    while (iterations < LIMIT && message != "q") {
        getUserInput(message, protocol);
        processProtocol(protocol, message);
        iterations++;
    }

    cout << "Exiting program!" << std::endl;
    return 0;
}

void getUserInput(std::string& message, std::string& protocol) {
    cout << "Enter the message you want to send to Alice: ";
    std::getline(cin, message);
    
    cout << "Enter the protocol you want to use: ";
    std::getline(cin, protocol);

    std::transform(protocol.begin(), protocol.end(), protocol.begin(), ::toupper);  // Convert to uppercase
}

void processProtocol(const std::string& protocol, const std::string& message) {
    std::string cipherText;

    if (protocol == "RSA" || protocol == "R") {
        RSA rsa;
        cipherText = rsa.encrypt(message);
    } else if (protocol == "COL") {
        ColumnarCipher col;
        cipherText = col.encrypt(message);
    } else if (protocol == "DH" || protocol == "DIFFIEHELLMAN") {
        DiffieHellman dh;
        dh.generateKey();
    } else if (protocol == "XOR") {
        XorCipher xorCipher;
        // TODO:
    } else if (protocol == "SUB") {
        SubstitutionCipher sub;
        cipherText = sub.encrypt(message);
    } else if (protocol == "ROT13") {
        ROT13 rot13;
        cipherText = rot13.encrypt(message);
    } else if (protocol == "Q") {
        cout << "Exiting program!" << std::endl;
        std::exit(0);
    } else {
        cout << protocol << " is an invalid command!" << endl;
    }
    cout << "[ CipherText: " << cipherText << " ]" << endl;
}
