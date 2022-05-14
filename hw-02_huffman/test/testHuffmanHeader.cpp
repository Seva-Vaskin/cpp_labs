#include "doctest.h"
#include "huffmanHeader.h"

#include <sstream>
#include <algorithm>

using namespace Huffman;

namespace {
    bool symbolSetsAreEqual(const std::string& s1, const std::vector<BinaryIO::byte>& s2) {
        bool ans = true;
        for (auto& i : s1)
            ans &= std::count(s2.begin(), s2.end(), i) != 0;
        for (auto& i : s2)
            ans &= std::count(s1.begin(), s1.end(), i) != 0;
        return ans;
    }
}

TEST_CASE("Build from regular text") {
    std::istringstream stream;
    SUBCASE("Empty") {
        auto header = HuffmanHeader::fromRegularText(stream);
        CHECK_EQ(header.huffmanTree().symbolsCount(), 0);
        CHECK_EQ(header.textLength(), 0);
        CHECK(symbolSetsAreEqual("", header.huffmanTree().symbols()));
        CHECK_EQ(header.bitSequenceLength(), 0);
    }

    SUBCASE("Single symbol") {
        std::string s(5, 'a');
        stream.str(s);
        auto header = HuffmanHeader::fromRegularText(stream);
        CHECK_EQ(header.huffmanTree().symbolsCount(), 1);
        CHECK(symbolSetsAreEqual(s, header.huffmanTree().symbols()));
        CHECK_EQ(header.textLength(), 5);
        CHECK_EQ(header.huffmanTree().getSequence('a').size(), 1);
        CHECK_EQ(header.bitSequenceLength(), 5);
    }

    SUBCASE("Two equal symbols") {
        std::string s = "abab";
        stream.str(s);
        auto header = HuffmanHeader::fromRegularText(stream);
        CHECK_EQ(header.huffmanTree().symbolsCount(), 2);
        CHECK(symbolSetsAreEqual(s, header.huffmanTree().symbols()));
        CHECK_EQ(header.textLength(), 4);
        CHECK_EQ(header.huffmanTree().getSequence('a').size(), 1);
        CHECK_EQ(header.huffmanTree().getSequence('b').size(), 1);
        CHECK_EQ(header.bitSequenceLength(), 4);
    }

    SUBCASE("Two not equal symbols") {
        std::string s = "aaab";
        stream.str(s);
        auto header = HuffmanHeader::fromRegularText(stream);
        CHECK_EQ(header.huffmanTree().symbolsCount(), 2);
        CHECK_EQ(header.textLength(), 4);
        CHECK_EQ(header.huffmanTree().getSequence('a').size(), 1);
        CHECK_EQ(header.huffmanTree().getSequence('b').size(), 1);
        CHECK_EQ(header.bitSequenceLength(), 4);
    }


    SUBCASE("3 equal symbols") {
        std::string s = "abc";
        stream.str(s);
        auto header = HuffmanHeader::fromRegularText(stream);
        CHECK_EQ(header.huffmanTree().symbolsCount(), 3);
        CHECK(symbolSetsAreEqual(s, header.huffmanTree().symbols()));
        CHECK_EQ(header.textLength(), 3);
        size_t aSize = header.huffmanTree().getSequence('a').size();
        size_t bSize = header.huffmanTree().getSequence('b').size();
        size_t cSize = header.huffmanTree().getSequence('c').size();
        CHECK_LE(1, aSize);
        CHECK_LE(aSize, 2);
        CHECK_LE(1, bSize);
        CHECK_LE(bSize, 2);
        CHECK_LE(1, bSize);
        CHECK_LE(cSize, 2);
        CHECK_EQ(aSize + bSize + cSize, 5);
        CHECK_EQ(header.bitSequenceLength(), 5);
    }

    SUBCASE("3 not equal symbols") {
        std::string s = "babcb";
        stream.str(s);
        auto header = HuffmanHeader::fromRegularText(stream);
        CHECK_EQ(header.huffmanTree().symbolsCount(), 3);
        CHECK(symbolSetsAreEqual(s, header.huffmanTree().symbols()));
        CHECK_EQ(header.textLength(), 5);
        CHECK_EQ(header.huffmanTree().getSequence('a').size() , 2);
        CHECK_EQ(header.huffmanTree().getSequence('b').size(), 1);
        CHECK_EQ(header.huffmanTree().getSequence('c').size(), 2);
        CHECK_EQ(header.bitSequenceLength(), 1 * 2 + 3 * 1 + 1 * 2);
    }

    SUBCASE("Rope header test") {
        std::string s;
        for (int i = 0; i < 4; i++)
            s += std::string(1 << i, char('a' + i));
        stream.str(s);
        auto header = HuffmanHeader::fromRegularText(stream);
        CHECK_EQ(header.huffmanTree().symbolsCount(), 4);
        CHECK(symbolSetsAreEqual(s, header.huffmanTree().symbols()));
        CHECK_EQ(header.textLength(), 15);
        CHECK_EQ(header.huffmanTree().getSequence('a').size(), 3);
        CHECK_EQ(header.huffmanTree().getSequence('b').size(), 3);
        CHECK_EQ(header.huffmanTree().getSequence('c').size(), 2);
        CHECK_EQ(header.huffmanTree().getSequence('d').size(), 1);
        CHECK_EQ(header.bitSequenceLength(), 1 * 3 + 2 * 3 + 4 * 2 + 8 * 1);
    }
}