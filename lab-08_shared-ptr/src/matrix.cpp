#include "matrix.hpp"
#include <algorithm>

Matrix::Matrix(size_t r, size_t c) {
    _rows = r;
    _cols = c;
    _data = new int*[_rows];

    for (size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols]();
    }
};

Matrix::~Matrix() {
    for (size_t i = 0; i < _rows; ++i) {
        delete[] _data[i];
    }

    delete[] _data;
}

Matrix::Matrix(const Matrix& other) {
    _rows = other._rows;
    _cols = other._cols;
    _data = new int*[_rows];

    for (size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols];
    }

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            _data[i][j] = other._data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    _rows = other._rows;
    _cols = other._cols;
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; i < _cols; j++) {
            _data[i][j] = other._data[i][j];
        }
    }
    return *this;
}

void Matrix::set(size_t i, size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(size_t i, size_t j) const {
    return _data[i][j];
}

size_t Matrix::get_rows() const {
    return _rows;
}

size_t Matrix::get_cols() const {
    return _cols;
}

bool Matrix::operator==(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols) {
        return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}
