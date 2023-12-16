#ifndef MATRICES_H
#define MATRICES_H

using namespace std;

#include <iostream>
#include "cryptography.h"
#include "constants.h"
#include <vector>
#include <string>
#include <bitset>
#include <iomanip>
#include <cstdlib>
#include "string_util.h"


template <typename T>
class Matrix {
    public:
        Matrix(int, int);
        Matrix(int);
        Matrix(std::vector<std::vector<T>>, int, int);

        
        /*
        * pre-condition A and B both have n rows and m columns
        *
        */
        Matrix operator+(const Matrix&);
        Matrix operator-(const Matrix&);

        /*
        * Matrix multiplication and division to be used assume n == m where n is the number 
        * of rows in A and m is the number of columns in B.
        */ 
        Matrix operator*(const Matrix&);
        Matrix operator*(double);
        Matrix operator/(double);

        Matrix operator%(double modulus);

        /*
        * Utility functions
        */ 
        Matrix augment(const Matrix&, const Matrix&);
        void insertColumn(int, T&);
        void printMatrix();
        void printColumnSpace();
        Matrix transpose();
        double determinant(const Matrix&);
        Matrix getSubMatrix(int, const Matrix&);

        // Requires determinant and adjugate
        Matrix inverse();

        static Matrix createIdentity(int);
        Matrix getAdjugate();

        vector<T> extractColumn(int);

        void swapColumn(int, int);
        void swapRow(int, int);
    
    private:
        int currentRow = 0;
        int previousColumn = 0;
        
        int rows_;
        int columns_;
        std::vector<std::vector<T>> M;
};

/// @brief  Constructs a n x m matrix
/// @param rows 
/// @param columns 
template <typename T>
Matrix<T>::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
   this->M.resize(rows, vector<T>(columns,0));
   for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            this->M[i][j] = 0;
        }
    }
}

/// @brief Constructs a square matrix of length n
/// @param size 
template <typename T>
Matrix<T>::Matrix(int size) : rows_(size), columns_(size) {
   this->M.resize(size, vector<T>(size,0));
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
template <typename T>
Matrix<T>::Matrix(vector<vector<T>> A, int rows, int columns) : rows_(rows), columns_(columns) {
   this->M.resize(rows, vector<T>(columns,0));
   for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            this->M[i][j] = A[i][j];
        }
    }
}

template <typename T>
/// @brief Prints out the contents of a matrix
void Matrix<T>::printMatrix() {
     cout << "--------------------------------------------------------------" << endl;
     for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            cout << setw(8) << this->M[i][j];
        }
        cout << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
}


template <typename T>
/// @brief Prints out the contents of a matrix
void Matrix<T>::printColumnSpace() {
    int length = 0;
    string s = "";
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < columns_; i++) {
        for (int j = 0; j < rows_; j++) {
            T elem = this->M[j][i];
            if (elem != ' ') {
                s += elem;
            }
        }
    }
    string result = "";
    for (size_t i = 0; i < s.length(); i++) {
        result += s[i];

        // Insert a space every fifth letter
        if ((i + 1) % BLOCK_LENGTH == 0 && i != s.length() - 1) {
            result += ' ';
        }
    }
    cout << result << '\n';
}



/// @brief 
/// @param B 
/// @return 
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& B) {
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
template <typename T>
Matrix<T> Matrix<T>::operator%(double modulus) {
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
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& B) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = this->M[i][j] - B.M[i][j];
        }
    }
    return result;
} 

template <typename T>
/// @brief 
/// @param B 
/// @return 
Matrix<T> Matrix<T>::operator*(const Matrix& B) {
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
template <typename T>
Matrix<T> Matrix<T>::operator*(double lambda) {
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
template <typename T>
Matrix<T> Matrix<T>::operator/(double lambda) {
    Matrix result(this->rows_, this->columns_);
    for(int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->columns_; j++) {
            result.M[i][j] = (double)(this->M[i][j] / lambda);
        }
    }
    return result;
} 
template <typename T>
/// @brief Creates an identity matrix with the pre-condition that rows and columns are equal
/// @param rows 
/// @param columns 
/// @return An n x n identity matrix
Matrix<T> Matrix<T>::createIdentity(int size) {
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

template <typename T>
void Matrix<T>::insertColumn(int columnNumber, T& elem) {
    if (columnNumber != previousColumn) {
        currentRow = 0;
    }
    this->M[currentRow++][columnNumber] = elem;
    previousColumn = columnNumber;
    

}
/// @brief Assuming A has more columns than b and their rows are of equal length
/// @param A 
/// @param b 
/// @return 
template <typename T>
Matrix<T> Matrix<T>::augment(const Matrix& A, const Matrix& b) {
    Matrix augmented(A.rows_, A.columns_ + b.columns_);

    return augmented;
}

/// @brief Returns A transpose
/// @param A 
/// @return 
template <typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix At(this->columns_, this->rows_);
    for (int i = 0; i < this->columns_; i++) {
        for (int j = 0; j < this->rows_; j++) {
            At.M[i][j] = this->M[j][i];
        }
    }
    return At;
}
// TODO: Requires adjugate 
/// @brief 
/// @return 
template <typename T>
Matrix<T> Matrix<T>::inverse() {
    if (determinant(Matrix(this->M, this->rows_, this->columns_)) == 0) {
        
    }
}
/// @brief Returns the determinant
/// @param A 
/// @return 
template <typename T>
double Matrix<T>::determinant(const Matrix& A) {
    if (A.rows_ == 2 && A.columns_ == 2) {
        int a = A.M[0][0], b = A.M[0][1];
        int c = A.M[1][0], d = A.M[1][1];
        return (a * d) - (b * c);
    } 
    // Otherwise it is a 3 x 3
    return (A.M[0][0] * determinant(getSubMatrix(0, A))) - (A.M[0][1] * determinant(getSubMatrix(1, A))) + (A.M[0][2] * determinant(getSubMatrix(2, A)));
}

/// @brief 
/// @param col 
/// @param subject 
/// @return 
template <typename T>
Matrix<T> Matrix<T>::getSubMatrix(int col, const Matrix& subject) {
    vector<vector<double>> subMatrix;
    for (int i = 1; i < subject.rows_ ; i++) {
        for(int j = 0; j < subject.columns_; j++) {
            if (j != col) {
                subMatrix[i][j] = subject.M[i][j];
            }
        }
    }
    return Matrix(subMatrix, 2, 2);
}
template <typename T>
Matrix<T> Matrix<T>::getAdjugate() {
    if (this->columns_ == 2 && this->rows_ == 2) {

    }
    return Matrix(2, 2);
}

template <typename T>
void Matrix<T>::swapColumn(int c1, int c2) {
    for(int i = 0; i < this->M.size(); i++) {
        swap(this->M[i][c1], this->M[i][c2]);
    }

}
template <typename T>
void Matrix<T>::swapRow(int r1, int r2) {
    for(int j = 0; j < this->M[0].size(); j++) {
        swap(this->M[r1][j], this->M[r2][j]);
    }

}

#endif 