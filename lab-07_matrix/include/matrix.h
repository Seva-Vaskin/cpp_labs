#pragma once

#include <cstdio>
#include <cstddef>
#include <cstring>
#include <cassert>
#include <algorithm>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);

    Matrix(const Matrix &m);

    ~Matrix();

    std::size_t get_rows() const;

    std::size_t get_cols() const;

    void set(std::size_t i, std::size_t j, int val);

    int get(std::size_t i, std::size_t j) const;

    void print(FILE *f) const;

    Matrix operator+(const Matrix &m) const;

    Matrix operator-(const Matrix &m) const;

    Matrix operator*(const Matrix &m) const;

    Matrix &operator+=(const Matrix &m);

    Matrix &operator-=(const Matrix &m);

    Matrix &operator*=(const Matrix &m);

    Matrix &operator=(const Matrix &m);

    bool operator==(const Matrix &m) const;

    bool operator!=(const Matrix &m) const;

private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;

    void swap(Matrix &m);
};

