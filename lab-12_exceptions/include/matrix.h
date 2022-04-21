#pragma once

#include <cstddef>
#include <iostream>
#include <cstring>

#include "matrix_exception.h"

namespace matrix {

    class Matrix {
    public:
        Matrix(size_t r, size_t c);

        Matrix(const Matrix &m);

        Matrix() : _rows(0), _cols(0), _data(nullptr) {}

        ~Matrix();

        size_t get_rows() const;

        size_t get_cols() const;

        void set(size_t i, size_t j, int val);

        int get(size_t i, size_t j) const;

        int &get(size_t i, size_t j);

        Matrix operator+(const Matrix &m) const;

        Matrix operator-(const Matrix &m) const;

        Matrix operator*(const Matrix &m) const;

        Matrix &operator+=(const Matrix &m);

        Matrix &operator-=(const Matrix &m);

        Matrix &operator*=(const Matrix &m);

        Matrix &operator=(const Matrix &m);

        bool operator==(const Matrix &m) const;

        bool operator!=(const Matrix &m) const;

        friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);

        friend std::istream &operator>>(std::istream &in, Matrix &matrix);

    private:
        size_t _rows;
        size_t _cols;
        int **_data;

        void swap(Matrix &m);
    };

}
