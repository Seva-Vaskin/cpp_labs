#include "registers.h"

namespace matrix {
    int Registers::parse_id(const std::string &str_id) {
        assert(str_id.size() == 2);
        assert(isdigit(str_id[1]));
        int result = str_id[1] - '0';
        assert(result < SIZE);
        return result;
    }

    void Registers::load(const std::string &str_id, const std::string &filename) {
        int id = parse_id(str_id);
        std::ifstream in(filename);
        Matrix matrix;
        in >> matrix;
        matrices[id] = matrix;
    }

    void Registers::print(const std::string &str_id) {
        int id = parse_id(str_id);
        std::cout << matrices[id];
    }

    void Registers::add(const std::string &str_id1, const std::string &str_id2) {
        int id1 = parse_id(str_id1);
        int id2 = parse_id(str_id2);
        matrices[id1] += matrices[id2];
    }

    void Registers::mul(const std::string &str_id1, const std::string &str_id2) {
        int id1 = parse_id(str_id1);
        int id2 = parse_id(str_id2);
        matrices[id1] *= matrices[id2];
    }

    int Registers::elem(const std::string &str_id, size_t row, size_t col) {
        int id = parse_id(str_id);
        return matrices[id].get(row, col);
    }

    Registers::Registers() {
        matrices = new Matrix[SIZE]();
    }

    Registers::~Registers() {
        delete[] matrices;
    }
}