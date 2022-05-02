#pragma once

#include <string>
#include <istream>
#include <fstream>
#include <stdexcept>
#include <vector>

namespace BinaryIO {
    typedef unsigned char byte;

    class BinaryReader {
    public:
        explicit BinaryReader(const std::string &filename);

        explicit BinaryReader(std::istream *in);

        BinaryReader() : _buf(0), _buf_size(0), _in(nullptr), _isEof(false) {};

        int readBit();

        bool isEof() const;

        uint64_t readNumber(size_t byteLength);

        std::vector<bool> readSequence(size_t sequenceSize);

        void flushBuf();

        ~BinaryReader();

    private:
        void updateByte();

    private:
        int _buf;
        byte _buf_size;
        std::istream *_in;
        bool _isEof;
    };

    class BinaryReaderError : public std::logic_error {
    public:
        explicit BinaryReaderError(const std::string &what) : std::logic_error(what) {}
    };
}