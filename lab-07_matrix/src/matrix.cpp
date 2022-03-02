#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int *[_rows];
    _data[0] = new int[_rows * _cols];
    for (std::size_t i = 0; i < _rows; i++)
        _data[i] = _data[0] + i * _cols;
    std::memset(_data[0], 0, _rows * _cols * sizeof(int));
}

std::size_t Matrix::get_rows() const {
    return _rows;
}

std::size_t Matrix::get_cols() const {
    return _cols;
}

Matrix::Matrix(const Matrix &m) : Matrix(m._rows, m._cols) {
    for (std::size_t r = 0; r < _rows; r++)
        for (std::size_t c = 0; c < _cols; c++)
            _data[r][c] = m._data[r][c];
}

Matrix::~Matrix() {
    delete[] _data[0];
    delete[] _data;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

void Matrix::print(FILE *f) const {
    for (std::size_t r = 0; r < _rows; r++) {
        for (std::size_t c = 0; c < _cols; c++) {
            fprintf(f, "%d", _data[r][c]);
            if (c + 1 < _cols)
                fprintf(f, " ");
            else
                fprintf(f, "\n");
        }
    }
}

Matrix &Matrix::operator+=(const Matrix &m) {
    for (std::size_t r = 0; r < _rows; r++)
        for (std::size_t c = 0; c < _cols; c++)
            _data[r][c] += m._data[r][c];
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &m) {
    for (std::size_t r = 0; r < _rows; r++)
        for (std::size_t c = 0; c < _cols; c++)
            _data[r][c] -= m._data[r][c];
    return *this;
}

Matrix Matrix::operator+(const Matrix &m) const {
    Matrix result(*this);
    result += m;
    return result;
}

Matrix Matrix::operator-(const Matrix &m) const {
    Matrix result(*this);
    result -= m;
    return result;
}

Matrix Matrix::operator*(const Matrix &m) const {
    assert(_cols == m._rows);
    Matrix result(_rows, m._cols);
    for (std::size_t r = 0; r < result._rows; r++)
        for (std::size_t c = 0; c < result._cols; c++)
            for (std::size_t j = 0; j < _cols; j++)
                result._data[r][c] += _data[r][j] * m._data[j][c];
    return result;
}

Matrix &Matrix::operator*=(const Matrix &m) {
    *this = *this * m;
    return *this;
}

Matrix &Matrix::operator=(const Matrix &m) {
    Matrix tmp(m);
    this->swap(tmp);
    return *this;
}

bool Matrix::operator==(const Matrix &m) const {
    bool result = true;
    for (std::size_t r = 0; r < _rows; r++)
        for (std::size_t c = 0; c < _cols; c++)
            result &= _data[r][c] == m._data[r][c];
    return result;
}

bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}

void Matrix::swap(Matrix &m) {
    std::swap(_rows, m._rows);
    std::swap(_cols, m._cols);
    std::swap(_data, m._data);
}
