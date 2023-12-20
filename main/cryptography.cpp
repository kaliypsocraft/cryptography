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
bool isCharacter(int c)
{
    return c >= 'A' && c <= 'Z';
}

/// @brief
/// @param length
/// @return
vector<int> generateKey(int length)
{

    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        int value = rand() % BYTE;
        key.push_back(value);
    }
    return key;
}

/// @brief 
/// @param message 
/// @return 
string SubstitutionCipher::encrypt(const string& message) {
    return "TODO";
}

/// @brief 
/// @param message 
/// @return 
string SubstitutionCipher::decrypt(const string& message) {
    string key = formatKey("THE", message.length());
    
    return "TODO";
}

string SubstitutionCipher::formatKey(const string& key, int length) {
    string formattedKey = "";
    while(formattedKey.length() < length) {
        formattedKey += key;
    }
    return formattedKey;
}


/// @brief
/// @param message
/// @return
vector<int> XorCipher::encrypt(const string &message)
{
    vector<int> cipherText;
    string modifiedMessage = removeSpaces(message);
    generateKey(modifiedMessage.length());
    for (int i = 0; i < modifiedMessage.length(); i++)
    {
        cipherText.push_back((key[i] ^ modifiedMessage[i]) % ASCII_BOUND);
    }
    return cipherText;
}

/// @brief
/// @param cipher
void XorCipher::decrypt(vector<int> cipher)
{
    vector<int> plainText;
    cout << "Deciphered: ";
    for (int i = 0; i < cipher.size(); i++)
    {
        plainText.push_back((key[i] ^ cipher[i]) % ASCII_BOUND);
    }
    for (const auto &elem : plainText)
    {
        cout << (char)elem;
    }
    cout << endl;
}

/// @brief
/// @param message
/// @return
string PolyAlphabeticCipher::encrypt(const string &message)
{
    string plainText = removeSpaces(message);
    string cipherText = "";
    string key = formatKey(RANDOM_KEY, plainText);

    for (int i = 0; i < plainText.size(); i++)
    {
        int plainCharacter = plainText[i] - 65;
        int keyCharacter = key[i] - 65;
        cipherText += ((plainCharacter + keyCharacter) % 26) + 65;
    }
    return cipherText;
}

/// @brief TODO:
/// @param cipher
/// @return
string PolyAlphabeticCipher::decrypt(const string &cipher)
{
    string cipherText = removeSpaces(cipher);
    string decrypedText = "";
    string key = formatKey(RANDOM_KEY, cipherText);

    for (int i = 0; i < cipherText.size(); i++)
    {
        int plainCharacter = cipherText[i] - 65;
        int keyCharacter = key[i] - 65;
        cipherText += ((plainCharacter + keyCharacter) % 26) + 65;
    }
    return cipherText;
}

string PolyAlphabeticCipher::formatKey(const string &key, const string &plainText)
{
    string formattedKey = key;
    int index = 0;
    while (formattedKey.size() < plainText.size())
    {
        formattedKey += toupper(plainText[index++]);
    }
    return formattedKey;
}

/// TODO:
/// @param message
/// @return
string ROT13::encrypt(const string &message)
{
    string deciphered = "";
    int index = 0;
    for (const auto &elem : message)
    {
        char c = toupper(elem);
        if (isCharacter(c))
        {
            c = ((c + 13) % 'Z');
            if (c < 'A')
            {
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
string ROT13::decrypt(const string &cipher)
{
    ROT13 temp;
    return temp.encrypt(cipher);
}

/// @brief TODO:
/// @param plainText
/// @return
string ColumnarCipher::encrypt(const string &plainText)
{
    string message = removeSpaces(plainText);
    message = formatMessage(message);
    int rowLength = ceil(message.length() / DEFAULT_KEY_LENGTH);

    vector<vector<char>> plainString = generateColumnar(message,
                                                        rowLength,
                                                        DEFAULT_KEY_LENGTH);

    int ordering[RANDOM_KEY.length()];
    getOrdering(ordering);

    Matrix<char> transposed(rowLength, DEFAULT_KEY_LENGTH);
    for (int i = 0; i < DEFAULT_KEY_LENGTH; i++) {
        for (int j = 0; j < rowLength; j++) {    
            transposed.insertColumn(ordering[i], plainString[j][i]);
        }
    }
    transposed.printMatrix();
    string cipherText = "";
    for (int i = 0; i < DEFAULT_KEY_LENGTH; i++) {
        for (int j = 0; j < rowLength; j++) {
            char elem = transposed.getElement(j, i);
            if (elem != ' ') {
                cipherText += transposed.getElement(j, i);
            }
        
        }
    }
    return cipherText;
}


/// @brief TODO:
/// @param cipherText
/// @return
string ColumnarCipher::decrypt(const string &cipherText)
{
    string nonsense = removeSpaces(cipherText);
    nonsense = formatMessage(nonsense);
    int rowLength = ceil(nonsense.length() / DEFAULT_KEY_LENGTH);
    vector<vector<char>> cipherString = generateDecryption(nonsense,
                                                        rowLength,
                                                        DEFAULT_KEY_LENGTH);
    Matrix<char> cipher(cipherString, rowLength, DEFAULT_KEY_LENGTH);
    cipher.printMatrix();
    int ordering[RANDOM_KEY.length()];
    getOrdering(ordering);

    for (int i = 0; i < RANDOM_KEY.length(); i++) {
        cout << ordering[i];
    }
    cout << '\n';

    Matrix<char> decryption(rowLength, DEFAULT_KEY_LENGTH);
    for (int i = 0; i < DEFAULT_KEY_LENGTH; i++) {
        for (int j = 0; j < rowLength; j++) {    
            decryption.insertColumn(i, cipherString[j][ordering[i]]);
        }
    }

    string decrypted = "";
    for (int i = 0; i < rowLength; i++) {
        for (int j = 0; j < DEFAULT_KEY_LENGTH; j++) {
            decrypted += decryption.getElement(i, j);
        }
    }

    decryption.printMatrix();
    return decrypted;
}

vector<vector<char>> ColumnarCipher::generateDecryption(const string& cipher, int rows, int columns) {
    vector<vector<char>> word;

    word.resize(rows, vector<char>(columns, 0));
    int index = 0;
    for (int j = 0; j < columns; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            word[i][j] = cipher[index++];
        }
    }
    return word;
}
/// @brief 
/// @param order 
void ColumnarCipher::getOrdering(int *order)
{
    string sorted = RANDOM_KEY;
    std::sort(sorted.begin(), sorted.end());

    for (int i = 0; i < RANDOM_KEY.length(); i++)
    {
        for (int j = 0; j < sorted.size(); j++)
        {
            if (RANDOM_KEY[i] == sorted[j])
            {
                order[i] = j;
            }
        }
    }
}

/// @brief
/// @param s
/// @param rows
/// @param vector
/// @return
vector<vector<char>> ColumnarCipher::generateColumnar(const string &s, int rows, int cols)
{
    vector<vector<char>> word;

    word.resize(rows, vector<char>(cols, 0));
    int index = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            word[i][j] = s[index++];
        }
    }
    return word;
}
