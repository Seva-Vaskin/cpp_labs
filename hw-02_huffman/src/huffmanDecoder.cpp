#include "huffmanDecoder.h"

namespace Huffman {
    HuffmanDecoder::~HuffmanDecoder() {
        delete _out;
    }

    HuffmanHeader HuffmanDecoder::decode() {
        HuffmanHeader header = HuffmanHeader::fromEncodedText(_reader);
        _reader.flushBuf();
        decodeBody(header);
        return header;
    }

    void HuffmanDecoder::decodeBody(const HuffmanHeader &header) {
        size_t bitsToRead = header.bitSequenceLength();
        while (bitsToRead) {
            BinaryIO::byte symbol = header.huffmanTree().decodeSymbol(_reader);
            size_t sequenceLength = header.huffmanTree().getSequence(symbol).size();
            if (sequenceLength > bitsToRead)
                throw HuffmanError("Broken file");
            bitsToRead -= sequenceLength;
            _out->put((char)symbol);
        }
    }
}