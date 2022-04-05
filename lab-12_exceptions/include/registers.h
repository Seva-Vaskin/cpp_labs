#pragma once

#include <cassert>
#include <algorithm>
#include <fstream>

#include "matrix.h"

namespace matrix {

    class Registers {
    public:
        static const int SIZE = 10;

        Registers();

        ~Registers();

        void load(const std::string &str_id, const std::string &filename);

        void print(const std::string &str_id);

        void add(const std::string &str_id1, const std::string& str_id2);

        void mul(const std::string &str_id1, const std::string& str_id2);

        int elem(const std::string &str_id, size_t rows, size_t cols);
    private:
        static int parse_id(const std::string &str_id);

    private:
        Matrix *matrices;
    };
}