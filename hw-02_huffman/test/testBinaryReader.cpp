#include "doctest.h"
#include "binaryReader.h"
#include <sstream>

using namespace BinaryIO;

TEST_CASE("Read bit tests") {
    auto stream = new std::istringstream;
    BinaryReader reader(stream);

    SUBCASE("Empty") {
        CHECK_EQ(reader.readBit(), EOF);
    }

    SUBCASE("One byte") {
        std::string s(1, '\x54');
        stream->str(s);
        CHECK_EQ(reader.readBit(), 0);
        CHECK_EQ(reader.readBit(), 1);
        CHECK_EQ(reader.readBit(), 0);
        CHECK_EQ(reader.readBit(), 1);
        CHECK_EQ(reader.readBit(), 0);
        CHECK_EQ(reader.readBit(), 1);
        CHECK_EQ(reader.readBit(), 0);
        CHECK_EQ(reader.readBit(), 0);
        CHECK_EQ(reader.readBit(), EOF);
    }

    SUBCASE("Multiple bytes") {
        std::string s(2, '\x54');
        stream->str(s);
        for (int i = 0; i < 2; i++) {
            CHECK_EQ(reader.readBit(), 0);
            CHECK_EQ(reader.readBit(), 1);
            CHECK_EQ(reader.readBit(), 0);
            CHECK_EQ(reader.readBit(), 1);
            CHECK_EQ(reader.readBit(), 0);
            CHECK_EQ(reader.readBit(), 1);
            CHECK_EQ(reader.readBit(), 0);
            CHECK_EQ(reader.readBit(), 0);
        }
        CHECK_EQ(reader.readBit(), EOF);
    }
}

TEST_CASE("Read number tests") {
    auto stream = new std::istringstream;
    BinaryReader reader(stream);

    SUBCASE("Empty") {
        CHECK_THROWS_AS(reader.readNumber(1), BinaryReaderError);
    }

    SUBCASE("One byte") {
        char expected = char(134);
        std::string s(1, expected);
        stream->str(s);
        char actual = (char)reader.readNumber(1);
        CHECK_EQ(actual, expected);
    }

    SUBCASE("Multiple bytes") {
        int expected = 134;
        std::string s(2, char(expected));
        stream->str(s);
        int actual = (int)reader.readNumber(2);
        CHECK_EQ(actual, expected * 256 + expected);
    }
}