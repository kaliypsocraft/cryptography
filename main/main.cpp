#include <iostream>
#include "cryptography.h"
#include <gmp.h>
#include "constants.h"
#include <gmpxx.h>
#include <vector>
#include <string>
#include <math.h>
#include <random>
#include <bitset>
#include <iomanip>
#include "matrices.h"
#include "matrices.cpp"
#include "string_util.h"

using std::vector, std::cout, std::cin, std::find;

string formatMessage(string s);
vector<vector<char>> generateColumnar(string s, int rows, int cols);
bool customOrder(char a, char b);

int main() {
    
    polyAlphabeticCipher test;
    cout << test.encrypt("meetatthefountain") << '\n';

    /*
    string s = "";
    cout << "Enter the message: " << '\n';
    cin >> s;
    s = formatMessage(s);
    
    vector<vector<char>> charTest = generateColumnar(s, (s.length() / 5), DEFAULT_KEY_LENGTH);
    Matrix<char> plain (charTest, (s.length() / 5), DEFAULT_KEY_LENGTH);
    plain.printMatrix();
    plain.printColumnSpace();
    */
    
    return 0;
}

vector<vector<char>> generateColumnar(string s, int rows, int cols) {
    vector<vector<char>> word;
    word.resize(rows, vector<char>(cols, 0));
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            word[i][j] = s[index++];
        }
    }
    return word;
}
