#include <iostream>
#include "cryptography.h"
#include <gmp.h>
#include "constants.h"
#include <gmpxx.h>
#include <vector>
#include <math.h>
#include <random>
#include <bitset>
#include <iomanip>
#include <cstdlib>
#include "matrices.h"

using namespace std;

// Constructor
// Initialise an empty matrix;
Matrix::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
   this->M.resize(rows, vector<double>(columns,0));
   for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            this->M[i][j] = 0;
        }
    }
}

// Constructor
// Intialise a pre-determined matrix
Matrix::Matrix(vector<vector<double>> A, int rows, int columns) : rows_(rows), columns_(columns) {
   this->M.resize(rows, vector<double>(columns,0));
   for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            this->M[i][j] = A[i][j];
        }
    }
}
void Matrix::printMatrix() {
     cout << "-------------------------------" << endl;
     for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(8) << this->M[i][j];
        }
        cout <<  endl;
    }
    cout << "-------------------------------" << endl;
}

/*
* pre-condition A and B both have n rows and m columns
*
*/
Matrix Matrix::operator+(const Matrix& B) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = this->M[i][j] + B.M[i][j];
        }
    }
    return result;
} 

// TODO:
Matrix Matrix::operator-(const Matrix& B) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = this->M[i][j] - B.M[i][j];
        }
    }
    return result;
} 


// TODO:
Matrix Matrix::operator*(const Matrix& B) {
    Matrix result(this->rows_, this->columns_);
    
    return result;
} 

// TODO:
Matrix Matrix::operator*(double lambda) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = this->M[i][j] * lambda;
        }
    }
    return result;
} 

// TODO:
Matrix Matrix::operator/(double lambda) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = (double)(this->M[i][j] / lambda);
        }
    }
    return result;
} 
