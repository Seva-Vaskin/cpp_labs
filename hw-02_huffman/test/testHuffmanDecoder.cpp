#include "doctest.h"
#include "huffmanDecoder.h"
#include <sstream>

TEST_CASE("Empty File") {
    auto in = new std::istringstream("");
    auto out = new std::ostringstream();
    Huffman::HuffmanDecoder decoder(in, out);
    decoder.decode();
    CHECK_EQ(out->str(), "");
}

TEST_CASE("OneSymbol") {
    std::string inStr(20, 0);
    inStr[17] = 'a';
    inStr[19] = '\x01';
    auto in = new std::istringstream(inStr);
    auto out = new std::ostringstream();
    Huffman::HuffmanDecoder decoder(in, out);
    decoder.decode();
    CHECK_EQ(out->str(), "a");
}