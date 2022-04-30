#include "doctest.h"
#include "binaryReader.h"
#include <sstream>

using namespace BinaryIO;


TEST_CASE("Binary read empty file") {
    auto stream = new std::istringstream;
    BinaryReader reader(stream);
    CHECK_EQ(reader.readBit(), EOF);
}

TEST_CASE("Binary read one byte") {
    std::string s(1, '\x54');
    auto stream = new std::istringstream(s);
    BinaryReader reader(stream);
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

TEST_CASE("Binary read multiple bytes") {
    std::string s(2, '\x54');
    auto stream = new std::istringstream(s);
    BinaryReader reader(stream);
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


TEST_CASE("Binary read number from empty file") {
    auto stream = new std::istringstream();
    BinaryReader reader(stream);
    CHECK_THROWS_AS(reader.readNumber(1), BinaryReaderError);
}

TEST_CASE("Binary read one byte") {
    char expected = char(134);
    std::string s(1, expected);
    auto stream = new std::istringstream(s);
    BinaryReader reader(stream);
    char actual = (char) reader.readNumber(1);
    CHECK_EQ(actual, expected);
}

TEST_CASE("Binary read multiple bytes") {
    int expected = 134;
    std::string s(2, char(expected));
    auto stream = new std::istringstream(s);
    BinaryReader reader(stream);
    int actual = (int) reader.readNumber(2);
    CHECK_EQ(actual, expected * 256 + expected);
}
