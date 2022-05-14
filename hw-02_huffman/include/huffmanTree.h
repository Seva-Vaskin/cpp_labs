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
        const std::vector<bool> &getSequence(BinaryIO::byte symbol) const;

        static HuffmanTree fromEncodedText(BinaryIO::BinaryReader &reader);

        HuffmanTree() : _root(nullptr) {}

        HuffmanTree(const HuffmanTree &tree) noexcept;

        ~HuffmanTree();

        explicit HuffmanTree(HuffmanTreeNode *root);

        BinaryIO::byte decodeSymbol(BinaryIO::BinaryReader& reader) const;

        size_t encodedByteSize() const noexcept;

        size_t symbolsCount() const noexcept;

        std::vector<BinaryIO::byte> symbols() const noexcept;

    private:
        void addSymbol(BinaryIO::byte symbol, const std::vector<bool> &sequence);

    private:
        HuffmanTreeNode *_root;
        std::map<BinaryIO::byte, std::vector<bool>> _symbolsMap;
    };
}