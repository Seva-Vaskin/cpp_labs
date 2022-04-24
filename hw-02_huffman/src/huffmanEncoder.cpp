#include "huffmanEncoder.h"

namespace Huffman {
    namespace {
        void encodeTree(BinaryIO::BinaryWriter &writer, const HuffmanTree &tree) {
            writer.writeNumber(tree.symbolsCount() - 1, 1);
            for (char symbol: tree.symbols()) {
                writer.writeNumber((BinaryIO::byte) symbol, 1);
                auto& sequence = tree.getSequence(symbol);
                assert(!sequence.empty() && sequence.size() <= 256);
                writer.writeNumber(sequence.size() - 1, 1);
                writer.writeSequence(sequence);
                writer.flushBuf();
            }
        }
    }

    HuffmanEncoder::~HuffmanEncoder() {
        delete _in;
    }

    HuffmanHeader HuffmanEncoder::encode() {
        auto header = HuffmanHeader::fromRegularText(*_in);
        if (header.textLength() == 0)
            return header;
        encodeHeader(header);
        _writer.flushBuf();
        encodeBody(header);
        _writer.flushBuf();
        return header;
    }

    void HuffmanEncoder::encodeHeader(const HuffmanHeader &header) {
        _writer.writeNumber(header.textLength() - 1, 8);
        _writer.writeNumber(header.bitSequenceLength() - 1, 8);
        encodeTree(_writer, header.huffmanTree());
    }

    void HuffmanEncoder::encodeBody(const HuffmanHeader &header) {
        _in->clear();
        _in->seekg(0);
        int symbol;
        while ((symbol = _in->get()) != EOF) {
            _writer.writeSequence(header.huffmanTree().getSequence((char)symbol));
        }
    }
}