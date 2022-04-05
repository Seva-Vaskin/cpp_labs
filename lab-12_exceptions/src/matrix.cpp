#include "matrix.h"

namespace matrix {
    Matrix::Matrix(size_t r, size_t c) {
        _rows = r;
        _cols = c;
        try {
            _data = nullptr;
            _data = new int *[_rows];
            _data[0] = new int[_rows * _cols];
        } catch (std::bad_alloc &exception) {
            delete _data;
            throw MatrixException("Unable to allocate memory.");
        }
        for (size_t i = 0; i < _rows; i++)
            _data[i] = _data[0] + i * _cols;
        std::memset(_data[0], 0, _rows * _cols * sizeof(int));
    }

    size_t Matrix::get_rows() const {
        return _rows;
    }

    size_t Matrix::get_cols() const {
        return _cols;
    }

    Matrix::Matrix(const Matrix &m) : Matrix(m._rows, m._cols) {
        for (size_t r = 0; r < _rows; r++)
            for (size_t c = 0; c < _cols; c++)
                _data[r][c] = m._data[r][c];
    }

    Matrix::~Matrix() {
        if (_data != nullptr)
            delete[] _data[0];
        delete[] _data;
    }

    void Matrix::set(size_t i, size_t j, int val) {
        _data[i][j] = val;
    }

    int Matrix::get(size_t i, size_t j) const {
        if (i >= _rows || j >= _cols)
            throw MatrixException("ACCESS: bad index.");
        return _data[i][j];
    }

    int &Matrix::get(size_t i, size_t j) {
        if (i >= _rows || j >= _cols)
            throw MatrixException("ACCESS: bad index.");
        return _data[i][j];
    }

    Matrix &Matrix::operator+=(const Matrix &m) {
        if (_rows != m._rows || _cols != m._cols)
            throw MatrixException("ADD: dimensions do not match.");
        for (size_t r = 0; r < _rows; r++)
            for (size_t c = 0; c < _cols; c++)
                _data[r][c] += m._data[r][c];
        return *this;
    }

    Matrix &Matrix::operator-=(const Matrix &m) {
        if (_rows != m._rows || _cols != m._cols)
            throw MatrixException("ADD: dimensions do not match.");
        for (size_t r = 0; r < _rows; r++)
            for (size_t c = 0; c < _cols; c++)
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
        if (_cols != m._rows)
            throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
        Matrix result(_rows, m._cols);
        for (size_t r = 0; r < result._rows; r++)
            for (size_t c = 0; c < result._cols; c++)
                for (size_t j = 0; j < _cols; j++)
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
        if (_cols != m._cols || _rows != m._rows)
            return false;
        return std::memcmp(_data[0], m._data[0], _rows * _cols * sizeof(int)) == 0;
    }

    bool Matrix::operator!=(const Matrix &m) const {
        return !(*this == m);
    }

    void Matrix::swap(Matrix &m) {
        std::swap(_rows, m._rows);
        std::swap(_cols, m._cols);
        std::swap(_data, m._data);
    }

    std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
        for (size_t i = 0; i < matrix._rows; i++) {
            for (size_t j = 0; j < matrix._cols; j++) {
                out << matrix.get(i, j);
                if (j + 1 < matrix._cols)
                    out << ' ';
            }
            if (i + 1 < matrix._rows)
                out << '\n';
        }
        return out;
    }

    std::istream &operator>>(std::istream &in, Matrix &matrix) {
        if (!in)
            throw MatrixException("LOAD: unable to open file.");
        size_t r, c;
        in >> r >> c;
        if (in.good())
            matrix = Matrix(r, c);
        for (size_t i = 0; i < r && in.good(); i++) {
            for (size_t j = 0; j < c && in.good(); j++) {
                in >> matrix.get(i, j);
            }
        }
        if (!in.good())
            throw MatrixException("LOAD: invalid file format.");
        return in;
    }
}
