#include <iostream>
#include "cryptography.h"
#include "matrices.h"

using namespace std;

int main() {
    Matrix m(3, 3);
    vector<vector<double>> test = {{1,2,3}, {4,5,6}, {7,8,9}};
    vector<vector<double>> test1 = {{1}, {1}, {1}}; // Essentially a 3D Vector with x,y,z coordinates
    Matrix b(test, 3, 3);
    Matrix b1(test1, 3, 1);

    Matrix scaled = b * b1;
    scaled.printMatrix();
   
    return 0;
}