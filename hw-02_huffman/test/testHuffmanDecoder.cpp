#include "doctest.h"
#include "huffmanDecoder.h"
#include <sstream>

//TEST_CASE("Decode empty File") {
//    std::string inStr;
//    auto in = new std::istringstream(inStr);
//    auto out = new std::ostringstream();
//    Huffman::HuffmanDecoder decoder(in, out);
//    decoder.decode();
//    std::string outStr = out->str();
//    CHECK_EQ(outStr, inStr);
//}

void createDecoder(std::istream* in, std::ostream* out) {
    Huffman::HuffmanDecoder decoder(in, out);
}

//TEST_CASE("Decode not existence file") {
//    auto in = new std::ifstream("thisFileNotExists.txt", std::ios::binary);
//    auto out = new std::stringstream();
//    CHECK_THROWS_AS(createDecoder(in, out), Huffman::HuffmanError);
//}

TEST_CASE("Decode one symbol") {
    std::string inStr(21, 0);
    inStr[17] = 'a';
    inStr[19] = '\x01';
    auto in = new std::istringstream(inStr);
    auto out = new std::ostringstream();
    Huffman::HuffmanDecoder decoder(in, out);
    decoder.decode();
    CHECK_EQ(out->str(), "a");
}