#include <iostream>
#include "cryptography.h"
#include <gmp.h>
#include "constants.h"
#include <gmpxx.h>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <random>
#include <bitset>
#include <cstdlib>

#define BYTE 255;

vector<int> key;

using namespace std;

/// @brief 
/// @param c 
/// @return 
bool isCharacter(int c) {
    return c >= 'A' && c <= 'Z';
}

/// @brief 
/// @param message 
/// @return 
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
/// @param length 
/// @return 
vector<int> generateKey(int length) {
    
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        int value = rand() % BYTE;
        key.push_back(value);
    }
    return key;
}

/// @brief 
/// @param message 
/// @return 
vector<int> xorCipher::encrypt(const string& message) {
    vector<int> cipherText;
    string modifiedMessage = removeSpaces(message);
    generateKey(modifiedMessage.length());
    for (int i = 0; i < modifiedMessage.length(); i++) {
        cipherText.push_back((key[i] ^ modifiedMessage[i]) % ASCII_BOUND);
    }
    return cipherText;
}

/// @brief 
/// @param cipher 
void xorCipher::decipher(vector<int> cipher) {
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

/// @brief 
/// @param message 
/// @return 
string polyAlphabeticCipher::encrypt(const string& message) {
    string plainText = removeSpaces(message);
    string cipherText = "";
    string key = formatKey(RANDOM_KEY, plainText);
    
    for (int i = 0; i < plainText.size(); i++) {
        int plainCharacter = plainText[i] - 65;
        int keyCharacter = key[i] - 65;
        cipherText += ((plainCharacter + keyCharacter) % 26) + 65;
    }
    return cipherText;
}

string polyAlphabeticCipher::formatKey(const string& key, const string& plainText) {
    string formattedKey = key;
    int index = 0;
    while (formattedKey.size() < plainText.size()) {
        formattedKey += toupper(plainText[index++]);
    }
    return formattedKey;
}

/// TODO:
/// @param message 
/// @return 
string ROT13::encrypt(const string& message) {
    string deciphered = "";
    int index = 0;
    for (const auto& elem : message) {
        char c = toupper(elem);
        if (isCharacter(c)) {
            c = ((c + 13) % 'Z');
            if (c < 'A') {
                c += ('A' - 1);
            }
        }
        deciphered += c;
    }
    return deciphered;
}

/// @brief 
/// @param plainText 
/// @return 
string columnarCipher::encrypt(const string& plainText) {

}

