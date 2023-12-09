#include "matrices.hpp"

class Matrix {
    private:
        int row;
        int column;
    public:
        Matrix(int row, int column) {
            this->row = row;
            this->column = column;
        }
};
