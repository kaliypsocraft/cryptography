#ifndef MATRICES_H
#define MATRICES_H

using namespace std;

#include <iostream>
#include "cryptography.h"
#include "constants.h"
#include <vector>
#include <cmath>
#include <string>
#include <bitset>
#include <iomanip>
#include <cstdlib>
#include "string_util.h"


template <typename T>
class Matrix {
    public:
        /*
            Basic constructors for creating our matricies
        */
        Matrix(int, int);
        Matrix(int);
        Matrix(std::vector<std::vector<T>>, int, int);

        
        /*
         pre-condition A and B both have n rows and m columns
        
        */
        Matrix operator+(const Matrix&);
        Matrix operator-(const Matrix&);

        /*
         Matrix multiplication and division to be used assume n == m where n is the number 
         of rows in A and m is the number of columns in B.
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
        Matrix getSubMatrix(int, int, const Matrix&);
       
        Matrix getCofactor();

        // Requires determinant and adjugate
        Matrix inverse();
        // Creates an identity matrix of size n provided by the user
        static Matrix createIdentity(int);
        Matrix getAdjugate();

        void swapColumn(int, int);
        void swapRow(int, int);

        T getElement(int, int);
    
    private:
        // Used for inserting columns
        int currentRow = 0;
        int previousColumn = 0;
        
        int rows_;
        int columns_;
        string resultString = "";
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

/// @brief 
/// @tparam T 
/// @param row 
/// @param col 
/// @return 
template <typename T>
T Matrix<T>::getElement(int row, int col) {
    return this->M[row][col];
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


/// @brief Prints out the contents of a matrix
template <typename T>
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

/// @brief Creates an identity matrix with the pre-condition that rows and columns are equal
/// @param rows 
/// @param columns 
/// @return An n x n identity matrix
template <typename T>
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

/// @brief 
/// @tparam T 
/// @param columnNumber 
/// @param elem 
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
/// @brief Assuming the determinant is non zero
/// @return 
template <typename T>
Matrix<T> Matrix<T>::inverse() {
    int det = determinant(*this);
    
    if (det != 0) {
        return getAdjugate() / determinant(*this);
    } else {
        throw std::runtime_error("Matrix is not square or has zero determinant");
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
    return (A.M[0][0] * determinant(getSubMatrix(0, 0, A))) - (A.M[0][1] * determinant(getSubMatrix(0, 1, A))) + (A.M[0][2] * determinant(getSubMatrix(0, 2, A)));
}

/// @brief 
/// @tparam T 
/// @return 
template <typename T>
Matrix<T> Matrix<T>::getCofactor() {
    Matrix<T> coFactors(3, 3);
    for (int i = 0; i < rows_; i++) {
        for(int j = 0; j < columns_; j++) {
            double det = determinant(getSubMatrix(i, j, *this));
            coFactors.M[i][j] = pow(-1, i + j + 2) * det;
        }
    }
    return coFactors;
}

/// @brief 
/// @param col 
/// @param subject 
/// @return 
template <typename T>
Matrix<T> Matrix<T>::getSubMatrix(int row, int col, const Matrix& subject) {
    vector<vector<double>> subMatrix;
    subMatrix.resize(subject.rows_ - 1 , std::vector<double>(subject.columns_ - 1 , 0.0));
    int subRow = 0;
    bool incrementSubRow = false;
    for (int i = 0; i < subject.rows_; i++) {
        int subCol = 0;
        for (int j = 0; j < subject.columns_; j++) {
            if (row != i && col != j) {
                subMatrix[subRow][subCol] = subject.M[i][j];
                subCol++;
                incrementSubRow = true;
            }
        }
        if (incrementSubRow) {
            subRow++;
            incrementSubRow = false;
        }

    }
    return Matrix(subMatrix, 2, 2);
}

/// @brief 
/// @tparam T 
/// @return 
template <typename T>
Matrix<T> Matrix<T>::getAdjugate() {
    if (this->columns_ == 2 && this->rows_ == 2) { 
        Matrix adjugate(2, 2);
        for (int row = 0; row < 2; row++) {
            for (int col = 0; col < 2; col++) {
                if (row == 0 && col == 0) {
                    adjugate.M[row][col] = this->M[1][1];
                } else if (row == 1 && col == 1) {
                    adjugate.M[row][col] = this->M[0][0];
                } else {
                    adjugate.M[row][col] = - (this->M[row][col]);
                }
            }
        }
        return adjugate;
    }

    return getCofactor().transpose();
}

/// @brief 
/// @tparam T 
/// @param c1 
/// @param c2 
template <typename T>
void Matrix<T>::swapColumn(int c1, int c2) {
    for(int i = 0; i < this->M.size(); i++) {
        swap(this->M[i][c1], this->M[i][c2]);
    }

}

/// @brief 
/// @tparam T 
/// @param r1 
/// @param r2 
template <typename T>
void Matrix<T>::swapRow(int r1, int r2) {
    for(int j = 0; j < this->M[0].size(); j++) {
        swap(this->M[r1][j], this->M[r2][j]);
    }

}

#endif 