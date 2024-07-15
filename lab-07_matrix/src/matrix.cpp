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

Matrix& Matrix::operator=(Matrix other) {
    std::swap(_rows, other._rows);
    std::swap(_cols, other._cols);
    std::swap(_data, other._data);

    return *this;
}

size_t Matrix::get_rows() const {
    return _rows;
}

size_t Matrix::get_cols() const {
    return _cols;
}

void Matrix::set(size_t i, size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(size_t i, size_t j) const {
    return _data[i][j];
}

void Matrix::print(FILE *f) const {
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            fprintf(f, "%d", _data[i][j]);
            if (j < _cols - 1) {
                fprintf(f, " ");
            }
        }
        
        fprintf(f, "\n");
    }
}

Matrix operate(const Matrix& m1, const Matrix& m2, int (*operation)(int, int)) {
    if (m1._rows != m2._rows || m1._cols != m2._cols) {
        return Matrix(0, 0);
    }

    Matrix result(m1._rows, m1._cols);

    for (size_t i = 0; i < m1._rows; ++i) {
        for (size_t j = 0; j < m1._cols; ++j) {
            result._data[i][j] = operation(m1._data[i][j], m2._data[i][j]);
        }
    }

    return result;
}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1);
    result += m2;
    return result;
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1);
    result -= m2;
    return result;
}



Matrix operator*(const Matrix& m1, const Matrix& m2) {
    if (m1._cols != m2._rows) {
        return Matrix(0, 0);
    }

    Matrix result(m1._rows, m2._cols);
    for (size_t i = 0; i < m1._rows; ++i) {
        for (size_t j = 0; j < m2._cols; ++j) {
            result._data[i][j] = 0;
            for (size_t k = 0; k < m1._cols; ++k) {
                result._data[i][j] += m1._data[i][k] * m2._data[k][j];
            }
        }
    }
    return result;
}


Matrix& Matrix::operator+=(const Matrix& m) {
    *this = operate(*this, m, [](int a, int b) { return a + b; });

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    *this = operate(*this, m, [](int a, int b) { return a - b; });
    
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    *this = *this * m;

    return *this;
}

bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1._rows != m2._rows || m1._cols != m2._cols) {
        return false;
    }

    for (size_t i = 0; i < m1._rows; ++i) {
        for (size_t j = 0; j < m1._cols; ++j) {
            if (m1._data[i][j] != m2._data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& m1, const Matrix& m2) {
    return !(m1 == m2);
}