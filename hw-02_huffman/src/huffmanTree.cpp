#include "huffmanTree.h"

namespace Huffman {
    namespace {
        void buildSymbolsMapDFS(HuffmanTreeNode *node, std::map<BinaryIO::byte, std::vector<bool>> &symbolsMap,
                                std::vector<bool> &sequence) noexcept {
            if (node->isTerminate()) {
                symbolsMap[node->symbol()] = sequence;
                return;
            }
            sequence.push_back(false);
            buildSymbolsMapDFS(node->go(0), symbolsMap, sequence);
            sequence.back() = true;
            buildSymbolsMapDFS(node->go(1), symbolsMap, sequence);
            sequence.pop_back();
        }

        void buildSymbolsMap(HuffmanTreeNode *root, std::map<BinaryIO::byte, std::vector<bool>> &symbolsMap) noexcept {
            std::vector<bool> sequence;
            if (root->isTerminate()) {
                symbolsMap[root->symbol()].push_back(false);
            } else {
                buildSymbolsMapDFS(root, symbolsMap, sequence);
            }
        }

        void addSymbolRecursively(
                HuffmanTreeNode *node, BinaryIO::byte symbol, const std::vector<bool> &sequence, size_t pos = 0) {
            assert(node != nullptr);
            if (pos == sequence.size()) {
                if (node->isTerminate())
                    throw HuffmanError("Sequence in huffman tree is ambiguous");
                *node = HuffmanTreeNode(symbol);
            } else {
                if (node->go(sequence[pos]) == nullptr) {
                    node->setNext(sequence[pos], new HuffmanTreeNode());
                }
                addSymbolRecursively(node->go(sequence[pos]), symbol, sequence, pos + 1);
            }
        }

        BinaryIO::byte decodeSymbolRecursively(HuffmanTreeNode *node, BinaryIO::BinaryReader &reader) {
            if (node == nullptr)
                throw HuffmanError("Undefined binary sequence");
            if (node->isTerminate())
                return node->symbol();
            else {
                int bit = reader.readBit();
                if (bit == EOF)
                    throw BinaryIO::BinaryReaderError("Unexpected end of file");
                return decodeSymbolRecursively(node->go((bool) bit), reader);
            }
        }
    }

    HuffmanTree::HuffmanTree(HuffmanTreeNode *root) : _root(root) {
        assert(root != nullptr);
        buildSymbolsMap(_root, _symbolsMap);
    }

    const std::vector<bool> &HuffmanTree::getSequence(BinaryIO::byte symbol) const {
        auto it = _symbolsMap.find(symbol);
        if (it == _symbolsMap.end())
            throw HuffmanError("Trying to get binary sequence of undefined symbol");
        return it->second;
    }

    size_t HuffmanTree::symbolsCount() const noexcept {
        return _symbolsMap.size();
    }

    HuffmanTree::HuffmanTree(const HuffmanTree &tree) noexcept {
        if (tree._root == nullptr)
            _root = nullptr;
        else
            _root = new HuffmanTreeNode(*tree._root);
        _symbolsMap = tree._symbolsMap;
    }

    HuffmanTree::~HuffmanTree() {
        delete _root;
    }

    std::vector<BinaryIO::byte> HuffmanTree::symbols() const noexcept {
        std::vector<BinaryIO::byte> result;
        for (auto &[symbol, _]: _symbolsMap)
            result.push_back(symbol);
        return result;
    }

    HuffmanTree HuffmanTree::fromEncodedText(BinaryIO::BinaryReader &reader) {
        auto tree = HuffmanTree();
        size_t symbolsCount = reader.readNumber(1) + 1;
        for (size_t i = 0; i < symbolsCount; i++) {
            BinaryIO::byte symbol = (BinaryIO::byte) reader.readNumber(1);
            size_t sequenceSize = reader.readNumber(1) + 1;
            auto sequence = reader.readSequence(sequenceSize);
            reader.flushBuf();
            tree.addSymbol(symbol, sequence);
        }
        return tree;
    }

    void HuffmanTree::addSymbol(BinaryIO::byte symbol, const std::vector<bool> &sequence) {
        if (_symbolsMap.count(symbol))
            throw HuffmanError("Multiple adding symbol to huffman tree");
        _symbolsMap[symbol] = sequence;
        if (_root == nullptr)
            _root = new HuffmanTreeNode();
        addSymbolRecursively(_root, symbol, sequence);
    }

    BinaryIO::byte HuffmanTree::decodeSymbol(BinaryIO::BinaryReader &reader) const {
        return decodeSymbolRecursively(_root, reader);
    }

    size_t HuffmanTree::encodedByteSize() const noexcept {
        if (_symbolsMap.empty())
            return 0;
        size_t totalSequencesLength = 0;
        for (auto& [_, sequence] : _symbolsMap)
            totalSequencesLength += (sequence.size() + 7) / 8;
        return 1 + 2 * symbolsCount() + totalSequencesLength;
    }
}