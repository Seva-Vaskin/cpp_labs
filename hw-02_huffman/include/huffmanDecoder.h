#pragma once

#include "binaryReader.h"
#include "huffmanHeader.h"
#include "iostream"

namespace Huffman {

    class HuffmanDecoder {
    public:
        HuffmanDecoder(std::istream *in, std::ostream *out) : _reader(in), _out(out) {};

        HuffmanHeader decode();

        ~HuffmanDecoder();

    private:
        void decodeBody(const HuffmanHeader &header);

    private:
        BinaryIO::BinaryReader _reader;
        std::ostream *_out;
    };

}

