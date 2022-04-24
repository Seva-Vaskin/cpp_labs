#include "doctest.h"
#include "huffmanEncoder.h"
#include <sstream>

TEST_CASE("Empty File") {
    auto in = new std::istringstream();
    auto out = new std::ostringstream();
    Huffman::HuffmanEncoder encoder(in, out);
    encoder.encode();
    CHECK_EQ(out->str(), "");
}

TEST_CASE("OneSymbol") {
    std::string inStr = "a";
    auto in = new std::istringstream(inStr);
    auto out = new std::ostringstream();
    Huffman::HuffmanEncoder encoder(in, out);
    encoder.encode();
    std::string outStr = out->str();
    CHECK_EQ(outStr.size(), 20);
    std::string expectedTextLength(8, 0);
    CHECK_EQ(outStr.substr(8, 8), expectedTextLength);
    std::string expectedBitLength(8, 0);
    CHECK_EQ(outStr.substr(0, 8), expectedBitLength);
    std::string expectedSymbolsInTree(1, 0);
    CHECK_EQ(outStr.substr(16, 1), expectedSymbolsInTree);
    std::string expectedSymbol(1, 'a');
    CHECK_EQ(outStr.substr(17, 1), expectedSymbol);
    // length of 'a' sequence
    CHECK_EQ(outStr[18], 0);
    // symbol 'a' encoded with 0 or 1
    CHECK_LE(outStr[19], 1);
    CHECK_LE(0, outStr[19]);
}