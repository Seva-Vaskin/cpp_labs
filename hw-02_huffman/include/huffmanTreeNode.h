#pragma once

#include "huffmanError.h"

namespace Huffman {
    class HuffmanTreeNode {
    public:
        HuffmanTreeNode() : _next0(nullptr), _next1(nullptr), _symbol(0), _isTerminate(false) {}

        HuffmanTreeNode(char symbol) : _next0(nullptr), _next1(nullptr), _symbol(symbol), _isTerminate(true) {}

        HuffmanTreeNode(const HuffmanTreeNode &node);

        ~HuffmanTreeNode();

        HuffmanTreeNode(HuffmanTreeNode *next0, HuffmanTreeNode *next1)
                : _next0(next0), _next1(next1), _symbol(0), _isTerminate(false) {}

        HuffmanTreeNode *go(bool bit) const;

        void setNext(bool bit, HuffmanTreeNode* nxt);

        bool isTerminate() const;

        char symbol() const;

    private:
        HuffmanTreeNode *_next0;
        HuffmanTreeNode *_next1;
        char _symbol;
        bool _isTerminate;
    };
}