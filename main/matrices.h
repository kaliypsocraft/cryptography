#ifndef MATRICES_H
#define MATRICES_H


#include <vector>

class Matrix {
    public:
        Matrix(int, int);
        Matrix(std::vector<std::vector<double>>, int, int);
        
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
        
        void printMatrix();
    
    private:
        int rows_;
        int columns_;
        std::vector<std::vector<double>> M;
};

#endif 