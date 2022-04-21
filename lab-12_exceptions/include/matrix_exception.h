#pragma once

#include <stdexcept>
#include <string>

namespace matrix {

    class MatrixException : public std::exception {
    public:
        explicit MatrixException(const std::string &message) : message_(message) {}

        ~MatrixException() override = default;

        const char *what() const noexcept override;

    private:
        std::string message_;
    };
}