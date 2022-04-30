#pragma once

#include <stdexcept>
#include <string>
#include <cassert>
#include <vector>

namespace ArgumentsParsing {
    enum RunTypes {
        Undefined,
        Compress,
        Uncompress,
    };

    class ArgumentsParser {
    public:
        ArgumentsParser(int argc, const char *argv[]);

        explicit ArgumentsParser(const std::vector<std::string> &argv);

        ~ArgumentsParser() = default;

        const std::string& file() const noexcept;
        const std::string& output() const noexcept;
        RunTypes runType() const noexcept;

    private:
        void setRunType(RunTypes newType);

    private:
        RunTypes _runType;
        std::string _file;
        std::string _output;
    };

    class ArgumentsParsingError : public std::logic_error {
    public:
        explicit ArgumentsParsingError(const std::string &what) : std::logic_error(what) {}
    };
}

