#pragma once

#include <iostream>
#include "huffmanHeader.h"
#include "binaryWriter.h"

namespace Huffman {

    class HuffmanEncoder {
    public:
        HuffmanEncoder(std::istream *in, std::ostream *out) : _in(in), _writer(out) {}

        HuffmanHeader encode();

        ~HuffmanEncoder();

    private:
        void encodeHeader(const HuffmanHeader& header);

        void encodeBody(const HuffmanHeader& header);

    private:
        std::istream *_in;
        BinaryIO::BinaryWriter _writer;
    };

}
