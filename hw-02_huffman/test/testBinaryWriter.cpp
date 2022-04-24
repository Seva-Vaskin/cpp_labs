#include "doctest.h"
#include "binaryWriter.h"
#include <sstream>

using namespace BinaryIO;

TEST_CASE("Write tests") {
    auto s = new std::stringstream();
    BinaryWriter writer(s);

    SUBCASE("Empty") {
        writer.flushBuf();
        CHECK_EQ(s->str(), "");
    }

    SUBCASE("One bit") {
        writer.writeBit(true);
        writer.flushBuf();
        CHECK_EQ(s->str(), "\x80");
    }

    SUBCASE("One byte") {
        for (int i = 0; i < 8; i++)
            writer.writeBit(true);
        writer.flushBuf();
        CHECK_EQ(s->str(), "\xff");
    }

    SUBCASE("Two bytes") {
        for (int i = 0; i < 8; i++)
            writer.writeBit(false);
        for (int i = 0; i < 8; i++)
            writer.writeBit(true);
        writer.flushBuf();
        std::string expected;
        expected += '\x00';
        expected += '\xff';
        CHECK_EQ(s->str(), expected);
    }

    SUBCASE("Partial byte") {
        for (int i = 0; i < 8; i++)
            writer.writeBit(false);
        for (int i = 0; i < 6; i++)
            writer.writeBit(true);
        writer.flushBuf();
        std::string expected;
        expected += '\x00';
        expected += '\xfc';
        CHECK_EQ(s->str(), expected);
    }

    SUBCASE("Binary sequence") {
        std::vector<bool> sequence = {true, true, false, false, true, false, true, true};
        writer.writeSequence(sequence);
        writer.flushBuf();
        std::string expected;
        expected += '\xcb';
        CHECK_EQ(s->str(), expected);
    }

    SUBCASE("One byte number writing") {
        writer.writeNumber(0x06, 1);
        writer.flushBuf();
        std::string expected;
        expected += '\x06';
        CHECK_EQ(s->str(), expected);
    }

    SUBCASE("Multiple bytes number writing") {
        writer.writeNumber(0x2872, 2);
        writer.flushBuf();
        std::string expected;
        expected += '\x28';
        expected += '\x72';
        CHECK_EQ(s->str(), expected);

    }
}