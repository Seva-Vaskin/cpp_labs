#pragma once

#include "huffmanError.h"
#include "binaryReader.h"

namespace Huffman {
    class HuffmanTreeNode {
    public:
        HuffmanTreeNode() : _next0(nullptr), _next1(nullptr), _symbol(0), _isTerminate(false) {}

        HuffmanTreeNode(BinaryIO::byte symbol) : _next0(nullptr), _next1(nullptr), _symbol(symbol), _isTerminate(true) {}

        HuffmanTreeNode(const HuffmanTreeNode &node);

        ~HuffmanTreeNode();

        HuffmanTreeNode(HuffmanTreeNode *next0, HuffmanTreeNode *next1)
                : _next0(next0), _next1(next1), _symbol(0), _isTerminate(false) {}

        HuffmanTreeNode *go(bool bit) const noexcept;

        void setNext(bool bit, HuffmanTreeNode* nxt);

        bool isTerminate() const noexcept;

        BinaryIO::byte symbol() const noexcept;

    private:
        HuffmanTreeNode *_next0;
        HuffmanTreeNode *_next1;
        BinaryIO::byte _symbol;
        bool _isTerminate;
    };
}