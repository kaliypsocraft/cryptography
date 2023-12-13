#include <iostream>
#include "cryptography.h"
#include <gmp.h>
#include "constants.h"
#include <gmpxx.h>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include <bitset>
#include <cstdlib>

#define BYTE 255;

vector<int> key;

using namespace std;

void decipher(vector<int> cipher);

vector<int> generateKey(int length) {
    
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        int value = rand() % BYTE;
        key.push_back(value);
    }
    return key;
}

string removeSpaces(string message) {
    string formatted = "";
    for (const auto& c : message) {
        if (c != ' ') {
            formatted += toupper(c);
        }
    }
    return formatted;
}

/// @brief 
/// @param message 
/// @return 
vector<int> xorCipher(string& message) {
    vector<int> cipherText;
    message = removeSpaces(message);
    generateKey(message.length());
    for (int i = 0; i < message.length(); i++) {
        cipherText.push_back((key[i] ^ message[i]) % ASCII_BOUND);
    }
    decipher(cipherText);
    return cipherText;
}

void decipher(vector<int> cipher) {
    vector<int> plainText;
    cout << "Deciphered: ";
    for (int i = 0; i < cipher.size(); i++) {
        plainText.push_back((key[i] ^ cipher[i]) % ASCII_BOUND);
    }
    for (const auto& elem : plainText) {
        cout << (char)elem;
    }
    cout << endl;
}

/// TODO: 
string autoCipher() {}

/// TODO:
/// @param message 
/// @return 
string ROT13(const string& message) {
    string deciphered = "";
    int index = 0;
    for (const auto& elem : message) {
        char c = toupper(elem);
        cout << elem << '\n';
        deciphered += c;
    }
    return deciphered;
}
string generateKey() {

}
string columnarCipher(const string& plainText) {
    
}


