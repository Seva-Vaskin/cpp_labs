#include "binaryWriter.h"

namespace BinaryIO {
    namespace {
        std::vector<bool> numberToBinarySequence(uint64_t number, int byteLength) {
            std::vector<bool> sequence;
            int bitLength = 8 * byteLength;
            for (int i = bitLength - 1; i >= 0; i--) {
                sequence.push_back(number >> i & 1);
            }
            return sequence;
        }
    }

    void BinaryWriter::writeBit(bool bit) {
        if (_buf_size == 8)
            flushBuf();
        _buf |= bit << (7 - _buf_size);
        _buf_size++;
    }

    void BinaryWriter::flushBuf() {
        if (_buf_size == 0)
            return;
        _out->put((std::ostream::char_type) _buf);
        _buf_size = 0;
        _buf = 0;
    }

    BinaryWriter::BinaryWriter(std::ostream *out) : BinaryWriter() {
        _out = out;
    }

    BinaryWriter::BinaryWriter(const std::string &filename) : BinaryWriter() {
        _out = new std::ofstream(filename, std::ios::binary);
    }

    BinaryWriter::~BinaryWriter() {
        flushBuf();
        delete _out;
    }

    void BinaryWriter::writeSequence(const std::vector<bool> &sequence) {
        for (bool bit: sequence)
            writeBit(bit);
    }

    void BinaryWriter::writeNumber(uint64_t number, int byteLength) {
        writeSequence(numberToBinarySequence(number, byteLength));
    }
}