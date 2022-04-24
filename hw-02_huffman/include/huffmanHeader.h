#pragma once

#include <iostream>
#include <map>
#include <queue>
#include "huffmanTree.h"
#include "binaryReader.h"

namespace Huffman {
    class HuffmanHeader {
    public:
        static HuffmanHeader fromRegularText(std::istream &in);

        static HuffmanHeader fromEncodedText(BinaryIO::BinaryReader &reader);

        HuffmanHeader(const HuffmanHeader &header) = default;

        HuffmanHeader() : _tree(), _textLength(0), _bitSequenceLength(0) {};

        HuffmanHeader(const HuffmanTree &tree, size_t textLength, size_t bitSequenceLength) :
                _tree(tree), _textLength(textLength), _bitSequenceLength(bitSequenceLength) {}

        ~HuffmanHeader() = default;

        size_t textLength() const;

        size_t encodedTextByteLength() const;

        size_t headerByteLength() const;

        size_t bitSequenceLength() const;

        const HuffmanTree &huffmanTree() const;

    private:
        HuffmanTree _tree;
        size_t _textLength;
        size_t _bitSequenceLength;
    };
}
