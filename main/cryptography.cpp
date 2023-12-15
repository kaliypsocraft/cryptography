#include <iostream>
#include "cryptography.h"
#include "constants.h"
#include "string_util.h"
#include <unordered_map>
#include <string>
#include "matrices.h"
#include <vector>
#include <math.h>
#include "sort.h"
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
vector<int> XorCipher::encrypt(const string& message) {
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
void XorCipher::decrypt(vector<int> cipher) {
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
string PolyAlphabeticCipher::encrypt(const string& message) {
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

/// @brief TODO:
/// @param cipher 
/// @return 
string PolyAlphabeticCipher::decrypt(const string& cipher) {
     return "TODO";
}

string PolyAlphabeticCipher::formatKey(const string& key, const string& plainText) {
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

/// @brief Since we rotate by 13 letters rotating twice gets us back to where we came from - in mod(26)
/// @param cipher 
/// @return 
string ROT13::decrypt(const string& cipher) {
    ROT13 temp;
    return temp.encrypt(cipher);
}

/// @brief TODO:
/// @param plainText 
/// @return 
string ColumnarCipher::encrypt(const string& plainText) {
    int rowLength = ceil(plainText.length() / DEFAULT_KEY_LENGTH);
    cout << plainText.length() << '\n';
    cout << DEFAULT_KEY_LENGTH << '\n';
    vector<vector<char>> plainString = generateColumnar(plainText, 
                                                        rowLength,
                                                        DEFAULT_KEY_LENGTH);
    Matrix<char> generator(plainString, rowLength, DEFAULT_KEY_LENGTH);
    generator.printMatrix();
    generator.printColumnSpace();
   
    int ordering[RANDOM_KEY.length()];
    getOrdering(ordering);
    for (int i = 0; i < RANDOM_KEY.length(); i++) {
        cout << ordering[i] << '\n';
    }
    
    return "TODO";
}

void ColumnarCipher::getOrdering(int* order) {

    vector<char> sorted(RANDOM_KEY.begin(), RANDOM_KEY.end());
    QuickSort<char> sorter;
    sorter.sort(sorted, 0, sorted.size() - 1);
    
    for (const auto& elem : sorted) {
        cout << elem << '\n';
    }
    for (int i = 0; i < RANDOM_KEY.length(); i++) {
        for (int j = 0; j < sorted.size(); j++) {
            if (RANDOM_KEY[i] == sorted[j]) {
                order[i] = j;
            }
        }
    }
}

/// @brief TODO:
/// @param cipherText 
/// @return 
string ColumnarCipher::decrypt(const string& cipherText) {
    return "TODO";
}

/// @brief 
/// @param s 
/// @param rows 
/// @param vector 
/// @return 
vector<vector<char>> ColumnarCipher::generateColumnar(const string& s, int rows, int cols) {
    vector<vector<char>> word;
    string message = removeSpaces(s);
    message = formatMessage(message);
    word.resize(rows, vector<char>(cols, 0));
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            word[i][j] = message[index++];
        }
    }
    return word;
}
