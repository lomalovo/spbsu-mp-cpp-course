#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <stdexcept>

class MatrixException : public std::runtime_error {
public:
    explicit MatrixException(const std::string& message) : std::runtime_error(message) {}
};

class Matrix {
private:
    std::vector<int> _data;
    int _rows;
    int _cols;
public:
    Matrix();
    Matrix(int rows, int cols);
    void loadFromFile(const std::string& filename);
    void print() const;
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    int getElement(int row, int col) const;
};

#endif // MATRIX_H
