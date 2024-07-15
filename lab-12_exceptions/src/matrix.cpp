#include "matrix.hpp"
#include <iostream>
#include <fstream>

Matrix::Matrix() : _data(0), _rows(0), _cols(0) {}

Matrix::Matrix(int rows, int cols) : _data(std::vector<int>(cols*rows, 0)), _rows(rows), _cols(cols) {}

void Matrix::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw MatrixException("LOAD: unable to open file.");
    }

    int rows, cols;
    file >> rows >> cols;
    if (file.fail() || rows <= 0 || cols <= 0) {
        throw MatrixException("LOAD: invalid file format.");
    }

    Matrix temp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> temp._data[i+j*rows];
            if (file.fail()) {
                throw MatrixException("LOAD: invalid file format.");
            }
        }
    }
    _data = temp._data;
    _rows = rows;
    _cols = cols;
}

void Matrix::print() const {
    for (int i = 0; i < _rows; i++) {
        if (_cols > 0) {
            std::cout << _data[i];
        }
        for (int j = 1; j < _cols; j++) {
            std::cout << " " << _data[i+j*_rows];
        }
        std::cout << std::endl;
    }
}


Matrix Matrix::operator+(const Matrix& rhs) const {
    if (_rows != rhs._rows || _cols != rhs._cols) {
        throw MatrixException("ADD: dimensions do not match.");
    }

    Matrix result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result._data[i+j*_rows] = _data[i+j*_rows] + rhs._data[i+j*_rows];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    if (_cols != rhs._rows) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }

    Matrix result(_rows, rhs._cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < rhs._cols; j++) {
            for (int k = 0; k < rhs._rows; k++) {
                result._data[i+j*_rows] += _data[i+k*_rows] * rhs._data[k+j*rhs._rows];
            }
        }
    }
    return result;
}

int Matrix::getElement(int row, int col) const {
    if (row < 0 || col < 0 || row >= static_cast<int>(_rows) || col >= static_cast<int>(_cols)) {
        throw MatrixException("ACCESS: bad index.");
    }
    return _data[row + _rows * col];
}
