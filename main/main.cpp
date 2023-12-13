#include <iostream>
#include "cryptography.h"
#include "constants.h"
#include <vector>
#include "matrices.h"
#include "matrices.cpp"

using std::vector, std::cout;

vector<vector<char>> generateColumnar(string s, int rows, int cols);

int main() {
    vector<vector<double>> test = {{1,2,3}, {4,5,6}};
    Matrix<double> m(test, 2, 3);
    vector<vector<double>> determinant = {{3,7}, {1,-4}};
    Matrix<double> test1(determinant, 2, 2);
    cout << m.determinant(test1) << '\n';

    string s = "ATTACKATDAWN";
    vector<vector<char>> charTest = generateColumnar(s, (s.length() / 5) + 1, 5);
    Matrix<char> plain (charTest, (s.length() / 5) + 1, 5);
    plain.printMatrix();



    
   
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

