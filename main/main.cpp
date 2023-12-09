#include <iostream>
#include "cryptography.h"
#include "matrices.h"

using namespace std;

int main() {
    Matrix m(3, 3);
    vector<vector<double>> test = {{1,2,3}, {4,5,6}, {7,8,9}};
    Matrix b(test, 3, 3);

    double scale = 2.0;
    Matrix sum = b - m;
    Matrix scaled = sum * scale;
    scaled.printMatrix();
    Matrix reduced = scaled / 4.0;
    reduced.printMatrix();
    return 0;
}