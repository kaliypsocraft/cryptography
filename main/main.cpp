#include <iostream>
#include "cryptography.h"
#include "constants.h"
#include "sort.h"
#include "matrices.h"
#include "string_util.h"

#define LIMIT 50

using std::vector, std::cout, std::cin, std::find;

int main() {
    cout << "[ Welcome to Kali's Cryptology Project ]" << std::endl;
    
    std::string protocol;
    std::string message;
    std::string cipherText;

    int iterations = 0;
    
    while (iterations < LIMIT && message != "q") {
        cout << "Enter the message you want to send to Alice: ";
        cin >> message;
        
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Enter the protocol which you want to use: ";
        std::getline(cin, protocol);
        
        if (protocol == "RSA" || protocol == "R") {
            RSA rsa;
            cipherText = rsa.encrypt(message);
        } else if (protocol == "COL") {
            ColumnarCipher col;
            cipherText = col.encrypt(message);
        } else if (protocol == "DH" || protocol == "DiffieHellman") {
            DiffieHellman dh;
            dh.generateKey();
        } else if (protocol == "XOR") {
            XorCipher x_or;
            x_or.encrypt(message);
        } else if (protocol == "SUB") {
            SubstitutionCipher sub;
            cipherText = sub.encrypt(message);
        } else if (protocol == "ROT13") {
            ROT13 rot13;
            cipherText = rot13.encrypt(message);
        } else if (protocol == "q") {
            cout << "Exiting program!" << std::endl;
            break;
        } else {
            cout << protocol << " is an invalid command!" << endl;
        }
        cout << "[ CipherText: " << cipherText + " ]" << endl;
        iterations++;
    }
    return 0;
}

