#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

namespace BinaryIO {
    typedef unsigned char byte;

    class BinaryWriter {
    public:
        explicit BinaryWriter(const std::string &filename);

        explicit BinaryWriter(std::ostream *out);

        void writeBit(bool bit);

        void writeNumber(uint64_t number, int byteLength);

        void writeSequence(const std::vector<bool>& sequence);

        void flushBuf();

        ~BinaryWriter();

        BinaryWriter() : _buf(0), _buf_size(0), _out(nullptr) {};

    private:
        byte _buf;
        byte _buf_size;
        std::ostream *_out;
    };

    class BinaryWriterError : public std::logic_error {
    public:
        explicit BinaryWriterError(const std::string &what) : std::logic_error(what) {}
    };
}