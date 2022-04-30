#include "argumentsParsing.h"

namespace ArgumentsParsing {

    namespace {
        std::vector<std::string> createVectorOfArguments(int argc, const char *argv[]) noexcept {
            std::vector<std::string> stringArgv(argc);
            for (int i = 0; i < argc; i++)
                stringArgv[i] = argv[i];
            return stringArgv;
        }
    }

    ArgumentsParser::ArgumentsParser(int argc, const char *argv[]) :
            ArgumentsParser(createVectorOfArguments(argc, argv)) {}

    ArgumentsParser::ArgumentsParser(const std::vector<std::string> &argv) : _runType(Undefined) {
        for (size_t i = 0; i < argv.size(); i++) {
            if (argv[i] == "-c")
                setRunType(Compress);
            else if (argv[i] == "-u")
                setRunType(Uncompress);
            else if (argv[i] == "-f" || argv[i] == "--file") {
                if (!_file.empty())
                    throw ArgumentsParsingError("Input file is assigned more than once");
                i++;
                if (i >= argv.size())
                    throw ArgumentsParsingError("No input file in arguments");
                _file = argv[i];
            } else if (argv[i] == "-o" || argv[i] == "--output") {
                if (!_output.empty())
                    throw ArgumentsParsingError("output file is assigned more than once");
                i++;
                if (i >= argv.size())
                    throw ArgumentsParsingError("No output file in arguments");
                _output = argv[i];
            }
        }
        if (_runType == Undefined)
            throw ArgumentsParsingError("Run type is not assigned");
        if (_file.empty())
            throw ArgumentsParsingError("Input file is not assigned");
        if (_output.empty())
            throw ArgumentsParsingError("output file is not assigned");
    }


    void ArgumentsParser::setRunType(RunTypes newType) {
        assert((newType == Compress || newType == Uncompress) && "You can set only Compress/Uncompress type");
        if (_runType != Undefined)
            throw ArgumentsParsingError("Run type is assigned more than once");
        _runType = newType;
    }

    const std::string &ArgumentsParser::file() const noexcept {
        return _file;
    }

    const std::string &ArgumentsParser::output() const noexcept {
        return _output;
    }

    RunTypes ArgumentsParser::runType() const noexcept {
        return _runType;
    }
}
