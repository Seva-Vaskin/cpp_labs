#include "doctest.h"

#include "argumentsParsing.h"

using namespace ArgumentsParsing;

TEST_CASE("Good arguments") {
    SUBCASE("Short arguments names, classic order") {
        ArgumentsParser parser = ArgumentsParser(std::vector<std::string>{"-c", "-f", "file.txt", "-o", "output.txt"});
        CHECK_EQ(parser.runType(), ArgumentsParsing::Compress);
        CHECK_EQ(parser.file(), "file.txt");
        CHECK_EQ(parser.output(), "output.txt");
    }

    SUBCASE("Long arguments names, unusual order") {
        ArgumentsParser parser = ArgumentsParser(
                std::vector<std::string>{"--file", "file.txt", "--output", "output.txt", "-u"});
        CHECK_EQ(parser.runType(), ArgumentsParsing::Uncompress);
        CHECK_EQ(parser.file(), "file.txt");
        CHECK_EQ(parser.output(), "output.txt");
    }

    SUBCASE("Mixed arguments names length, unusual order") {
        ArgumentsParser parser = ArgumentsParser(
                std::vector<std::string>{"-f", "file.txt", "--output", "output.txt", "-u"});
        CHECK_EQ(parser.runType(), ArgumentsParsing::Uncompress);
        CHECK_EQ(parser.file(), "file.txt");
        CHECK_EQ(parser.output(), "output.txt");
    }
}

TEST_CASE("Bad arguments") {
    SUBCASE("Assign argument twice") {
        CHECK_THROWS_AS(
                ArgumentsParser(std::vector<std::string>{"-c", "-f", "f1.txt", "-f", "f2.txt", "-o", "output.txt"}),
                ArgumentsParsingError
        );
        CHECK_THROWS_AS(
                ArgumentsParser(std::vector<std::string>{"-c", "-f", "file.txt", "-o", "o1.txt", "-o", "o2.txt"}),
                ArgumentsParsingError
        );
        CHECK_THROWS_AS(
                ArgumentsParser(std::vector<std::string>{"-c", "-f", "file.txt", "-o", "output.txt", "-u"}),
                ArgumentsParsingError
        );
    }
    SUBCASE("Missed argument") {
        CHECK_THROWS_AS(ArgumentsParser(std::vector<std::string>{"-f", "file.txt", "-o", "output.txt"}),
                        ArgumentsParsingError);
        CHECK_THROWS_AS(ArgumentsParser(std::vector<std::string>{"-c", "-o", "output.txt"}),
                        ArgumentsParsingError);
        CHECK_THROWS_AS(ArgumentsParser(std::vector<std::string>{"-c", "-f", "file.txt"}),
                        ArgumentsParsingError);
    }
    SUBCASE("Flag without file") {
        CHECK_THROWS_AS(ArgumentsParser(std::vector<std::string>{"-c", "-o", "output.txt", "-f"}),
                        ArgumentsParsingError);
        CHECK_THROWS_AS(ArgumentsParser(std::vector<std::string>{"-c", "-f", "file.txt", "-o"}),
                        ArgumentsParsingError);
    }
}