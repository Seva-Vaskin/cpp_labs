#pragma once

#include <stdexcept>

namespace Huffman {
    class HuffmanError : public std::logic_error {
    public:
        explicit HuffmanError(const std::string &what) : std::logic_error(what) {}
    };
}