#include "doctest.h"
#include <string>
#include <sstream>
#include "huffmanDecoder.h"
#include "huffmanEncoder.h"

std::pair<std::string, std::string> runSample(const std::string& sampleName) {
    std::string samplePath = "../samples/" + sampleName;
    auto in = std::ifstream(samplePath.c_str(), std::ios::binary);
    if (in.fail())
        return {"", "something wrong with sample file"};
    std::string input;
    while (true) {
        int symbol = in.get();
        if (symbol == EOF)
            break;
        input.push_back(symbol);
    }
    auto encoderIn = new std::stringstream(input);
    auto encoderOut = new std::stringstream();
    Huffman::HuffmanEncoder encoder(encoderIn, encoderOut);
    encoder.encode();
    std::string encodeResult = encoderOut->str();
    auto decoderIn = new std::stringstream(encodeResult);
    auto decoderOut = new std::stringstream();
    Huffman::HuffmanDecoder decoder(decoderIn, decoderOut);
    decoder.decode();
    std::string output = decoderOut->str();
    return {input, output};
}

TEST_CASE("Samples") {
    SUBCASE("Empty file") {
        auto res = runSample("empty.txt");
        CHECK_EQ(res.first, res.second);
    }

    SUBCASE("Single symbol") {
        auto res = runSample("singleSymbol.txt");
        CHECK_EQ(res.first, res.second);
    }

    SUBCASE("Multiple symbols") {
        auto res = runSample("multipleSymbols.txt");
        CHECK_EQ(res.first, res.second);
    }

    SUBCASE("More symbols") {
        auto res = runSample("moreSymbols.txt");
        CHECK_EQ(res.first, res.second);
    }

    SUBCASE("All symbols") {
        auto res = runSample("allSymbols.txt");
        CHECK_EQ(res.first, res.second);
    }

    SUBCASE("Big random file") {
        auto res = runSample("bigRandomFile.txt");
        CHECK_EQ(res.first, res.second);
    }
}
