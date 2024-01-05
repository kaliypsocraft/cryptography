#include <iostream>
#include "cryptography.h"
#include "constants.h"
#include "sort.h"
#include "matrices.h"
#include "string_util.h"

using std::vector, std::cout, std::cin, std::find;

int main() {
    cout << "[ Welcome to Kali's Cryptology Project ]" << std::endl;
    std::string input = "";
    system("sleep 1");
    while (true) {
        cout << "Enter the protocol which you want to use: ";
        cin >> input;
        if (input == "RSA" || input == "R") {

        } else if (input == "DH" || input == "DiffieHellman") {
            DiffieHellman dh;
            dh.encrypt("hello");
        } else if (input == "q") {
            cout << "Exiting program!" << std::endl;
            break;
        }
    }
    return 0;
}

