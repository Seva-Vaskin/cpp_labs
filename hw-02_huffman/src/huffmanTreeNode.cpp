#include "huffmanTreeNode.h"

namespace Huffman {
    HuffmanTreeNode *Huffman::HuffmanTreeNode::go(bool bit) const noexcept {
        if (bit)
            return _next1;
        else
            return _next0;
    }

    bool HuffmanTreeNode::isTerminate() const noexcept {
        return _isTerminate;
    }

    BinaryIO::byte HuffmanTreeNode::symbol() const noexcept {
        return _symbol;
    }

    HuffmanTreeNode::HuffmanTreeNode(const HuffmanTreeNode &node) {
        if (node._next0 != nullptr) {
            _next0 = new HuffmanTreeNode(*node._next0);
        } else {
            _next0 = nullptr;
        }
        if (node._next1 != nullptr) {
            _next1 = new HuffmanTreeNode(*node._next1);
        } else {
            _next1 = nullptr;
        }
        _symbol = node._symbol;
        _isTerminate = node._isTerminate;
    }

    HuffmanTreeNode::~HuffmanTreeNode() {
        delete _next0;
        delete _next1;
    }

    void HuffmanTreeNode::setNext(bool bit, HuffmanTreeNode *nxt) {
        if (bit) {
            if (_next1 != nullptr)
                throw HuffmanError("Huffman tree is ambiguous");
            _next1 = nxt;
        }
        else {
            if (_next0 != nullptr)
                throw HuffmanError("Huffman tree is ambiguous");
            _next0 = nxt;
        }
    }

}