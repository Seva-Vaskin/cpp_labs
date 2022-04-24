#pragma once

#include "huffmanTreeNode.h"
#include <istream>
#include <map>
#include <vector>
#include <queue>
#include <stdexcept>
#include <cassert>
#include <numeric>
#include "binaryReader.h"
#include "huffmanError.h"

namespace Huffman {
    class HuffmanTree {
    public:
        const std::vector<bool> &getSequence(char symbol) const;

        static HuffmanTree fromEncodedText(BinaryIO::BinaryReader &reader);

        HuffmanTree() : _root(nullptr) {}

        HuffmanTree(const HuffmanTree &tree);

        ~HuffmanTree();

        explicit HuffmanTree(HuffmanTreeNode *root);

        char decodeSymbol(BinaryIO::BinaryReader& reader) const;

        size_t encodedByteSize() const;

        size_t symbolsCount() const;

        std::vector<char> symbols() const;

        size_t bitsToAlign() const;

    private:
        void addSymbol(char symbol, const std::vector<bool> &sequence);

    private:
        HuffmanTreeNode *_root;
        std::map<char, std::vector<bool>> _symbolsMap;
    };
}