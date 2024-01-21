#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "cryptography.h"
#include "constants.h"
#include "sort.h"
#include "tree.h"
#include "matrices.h"
#include "string_util.h"

using std::vector, std::cout, std::cin, std::find;

const int LIMIT = 50;

// Function prototypes
void getUserInput(std::string& message, std::string& protocol);
void processProtocol(const std::string& protocol, const std::string& message);

int main() {
    cout << "[ Welcome to Kali's Cryptology Project ]" << std::endl;
    
    vector<std::string> input = {"helloworld", "hellomom", "hellodad", "iamacompetentman"};
    MerkleTree<std::string> tree;
    vector<vector<MerkleNode<std::string>>> MT = tree.initialProtocol(input);
    vector<MerkleProof<std::string>> proof = tree.generateMerkleProof(2, MT);

    for (int i = 0; i < proof.size(); i++) {
        cout << proof[i].hash << "\n";
    }

    //vector<std::string> valid_input = {"936a185caaa266bb9cbe981e9e05cb78cd732b0b3280eb944412bb6f8f8f07af", "d9581e7af6def52328ad6914e8492bb6cee685705ccec565f6fec1066cadf518", " 0b0373712c4f0568173cc209611e26c0bc62b700b59b50045279f5b711ceaf59"};
    /*
    std::string message;
    std::string protocol;

    int iterations = 0;
    
    while (iterations < LIMIT && message != "q") {
        getUserInput(message, protocol);
        processProtocol(protocol, message);
        iterations++;
    }
    */
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
