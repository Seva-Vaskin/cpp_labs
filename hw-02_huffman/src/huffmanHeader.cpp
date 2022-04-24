#include "huffmanHeader.h"

namespace Huffman {
    namespace {
        void preprocessText(std::istream &in, std::map<char, size_t> &frequency, size_t &textLength) {
            in.clear();
            in.seekg(0);
            textLength = 0;
            int symbol;
            while ((symbol = in.get()) != EOF) {
                frequency[(char) symbol]++;
                textLength++;
            }
        }

        size_t findOutBitSequenceLength(const std::map<char, size_t> &frequency, const HuffmanTree &huffmanTree) {
            size_t length = 0;
            for (auto [symbol, symFrequency]: frequency) {
                length += symFrequency * huffmanTree.getSequence(symbol).size();
            }
            return length;
        }
    }

    HuffmanHeader HuffmanHeader::fromRegularText(std::istream &in) {
        std::map<char, size_t> frequency;
        size_t textLength;
        preprocessText(in, frequency, textLength);
        if (frequency.empty())
            return {HuffmanTree(), 0, 0};
        std::priority_queue<
                std::pair<size_t, HuffmanTreeNode *>,
                std::vector<std::pair<size_t, HuffmanTreeNode *>>,
                std::greater<>> nodes;
        for (auto &[symbol, count]: frequency) {
            nodes.emplace(count, new HuffmanTreeNode(symbol));
        }
        while (nodes.size() > 1) {
            auto [count1, node1] = nodes.top();
            nodes.pop();
            auto [count2, node2] = nodes.top();
            nodes.pop();
            nodes.emplace(count1 + count2, new HuffmanTreeNode(node1, node2));
        }
        auto huffmanTree = HuffmanTree(nodes.top().second);
        size_t bitSequenceLength = findOutBitSequenceLength(frequency, huffmanTree);
        return {huffmanTree, textLength, bitSequenceLength};
    }

    HuffmanHeader HuffmanHeader::fromEncodedText(BinaryIO::BinaryReader &reader) {
        if (reader.isEof())
            return {};
        size_t textLength = reader.readNumber(8) + 1;
        size_t bitSequenceLength = reader.readNumber(8) + 1;
        HuffmanTree tree = HuffmanTree::fromEncodedText(reader);
        return {tree, textLength, bitSequenceLength};
    }


    size_t HuffmanHeader::textLength() const {
        return _textLength;
    }

    const HuffmanTree &HuffmanHeader::huffmanTree() const {
        return _tree;
    }

    size_t HuffmanHeader::bitSequenceLength() const {
        return _bitSequenceLength;
    }

    size_t HuffmanHeader::encodedTextByteLength() const {
        return (_bitSequenceLength + 7) / 8;
    }

    size_t HuffmanHeader::headerByteLength() const {
        if (_textLength == 0)
            return 0;
        return 16 + _tree.encodedByteSize();
    }
}