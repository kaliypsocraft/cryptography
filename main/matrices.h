#ifndef MATRICES_H
#define MATRICES_H


#include <vector>
#include <string>

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
        int rows_;
        int columns_;
        std::vector<std::vector<T>> M;
};

#endif 