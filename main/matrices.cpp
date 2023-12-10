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

/// @brief  Constructs a n x m matrix
/// @param rows 
/// @param columns 
Matrix::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
   this->M.resize(rows, vector<double>(columns,0));
   for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            this->M[i][j] = 0;
        }
    }
}

/// @brief Constructs a square matrix of length n
/// @param size 
Matrix::Matrix(int size) : rows_(size), columns_(size) {
   this->M.resize(size, vector<double>(size,0));
   for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            this->M[i][j] = 0;
        }
    }
}

/// @brief Creates an n x m matrix with pre-determined values
/// @param A 
/// @param rows 
/// @param columns 
Matrix::Matrix(vector<vector<double>> A, int rows, int columns) : rows_(rows), columns_(columns) {
   this->M.resize(rows, vector<double>(columns,0));
   for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            this->M[i][j] = A[i][j];
        }
    }
}

/// @brief Prints out the contents of a matrix
void Matrix::printMatrix() {
     cout << "--------------------------------------------------------------" << endl;
     for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            cout << setw(8) << this->M[i][j];
        }
        cout << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
}


/// @brief 
/// @param B 
/// @return 
Matrix Matrix::operator+(const Matrix& B) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = this->M[i][j] + B.M[i][j];
        }
    }
    return result;
} 

/// @brief 
/// @param B 
/// @return 
Matrix Matrix::operator%(double modulus) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = (int)this->M[i][j] % (int)modulus;
        }
    }
    return result;
} 

/// @brief 
/// @param B 
/// @return 
Matrix Matrix::operator-(const Matrix& B) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = this->M[i][j] - B.M[i][j];
        }
    }
    return result;
} 


/// @brief 
/// @param B 
/// @return 
Matrix Matrix::operator*(const Matrix& B) {
    // As a 3x3 . 3x1 matrix turns into a 3x1 matrix
    Matrix result(this->rows_, B.columns_);
     for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < B.columns_; j++) {
           for (int k = 0; k < this->columns_; k++) {
                    result.M[i][j] += this->M[i][k] * B.M[k][j];
                } 
        }
    }
    return result;
} 
 /// @brief 
 /// @param 
 /// @return 
Matrix Matrix::operator*(double lambda) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = this->M[i][j] * lambda;
        }
    }
    return result;
} 

/// @brief 
/// @param lambda 
/// @return 
Matrix Matrix::operator/(double lambda) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = (double)(this->M[i][j] / lambda);
        }
    }
    return result;
} 

/// @brief Creates an identity matrix with the pre-condition that rows and columns are equal
/// @param rows 
/// @param columns 
/// @return An n x n identity matrix
Matrix Matrix::createIdentity(int size) {
    Matrix I(size);
    for (int i = 0; i < I.rows_; i++) {
        for (int j = 0; j < I.columns_; j++) {
            if (i == j) {
                I.M[i][j] = 1;
            } else {
                I.M[i][j] = 0;
            }
        }
    }
    return I;
}

/// @brief Assuming A has more columns than b and their rows are of equal length
/// @param A 
/// @param b 
/// @return 
Matrix Matrix::augment(const Matrix& A, const Matrix& b) {
    Matrix augmented(A.rows_, A.columns_ + b.columns_);

    return augmented;
}