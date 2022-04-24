#include <iostream>
#include <fstream>
#include "argumentsParsing.h"
#include "binaryWriter.h"
#include "binaryReader.h"
#include "huffmanEncoder.h"
#include "huffmanDecoder.h"

int main(int argc, const char *argv[]) {
    try {
        ArgumentsParsing::ArgumentsParser parser(argc, argv);
        assert(parser.runType() != ArgumentsParsing::Undefined);
        BinaryIO::BinaryReader reader(parser.output());
        auto in = new std::ifstream(parser.file(), std::ios::binary);
        auto out = new std::ofstream(parser.output(), std::ios::binary);
        if (in->bad() || out->bad())
            throw std::ios_base::failure("Troubles with input/output");
        if (parser.runType() == ArgumentsParsing::Compress) {
            Huffman::HuffmanEncoder encoder(in, out);
            auto header = encoder.encode();
            std::cout << header.textLength() << std::endl
                      << header.encodedTextByteLength() << std::endl
                      << header.headerByteLength() << std::endl;
        } else if (parser.runType() == ArgumentsParsing::Uncompress) {
            Huffman::HuffmanDecoder decoder(in, out);
            auto header = decoder.decode();
            std::cout << header.encodedTextByteLength() << std::endl
                      << header.textLength() << std::endl
                      << header.headerByteLength() << std::endl;
        }
    }
    catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    return 0;
}