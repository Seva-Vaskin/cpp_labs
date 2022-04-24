#include "binaryReader.h"

namespace BinaryIO {
    BinaryReader::BinaryReader(std::istream *in) : BinaryReader() {
        _in = in;
    }

    BinaryReader::BinaryReader(const std::string &filename) : BinaryReader() {
        _in = new std::ifstream(filename, std::ios::binary);
    }

    int BinaryReader::readBit() {
        updateByte();
        if (_isEof)
            return EOF;
        _buf_size--;
        return _buf >> (_buf_size) & 1;
    }

    BinaryReader::~BinaryReader() {
        delete _in;
    }

    void BinaryReader::updateByte() {
        if (_isEof || _buf_size != 0)
            return;
        flushBuf();
    }

    uint64_t BinaryReader::readNumber(size_t byteLength) {
        size_t bitLength = byteLength * 8;
        uint64_t result = 0;
        for (size_t i = 0; i < bitLength; i++) {
            int bit = readBit();
            if (bit == EOF)
                throw BinaryReaderError("Unexpected end of file");
            result |= bool(bit) << (bitLength - 1 - i);
        }
        return result;
    }

    std::vector<bool> BinaryReader::readSequence(size_t sequenceSize) {
        std::vector<bool> result;
        for (size_t i = 0; i < sequenceSize; i++) {
            int bit = readBit();
            if (bit == EOF)
                throw BinaryReaderError("Unexpected end of file");
            result.push_back((bool)bit);
        }
        return result;
    }

    bool BinaryReader::isEof() const {
        return _in->eof() || (_buf_size == 0 && _in->peek() == EOF);
    }

    void BinaryReader::flushBuf() {
        if (_buf_size == 8)
            return;
        _buf = _in->get();
        _isEof |= _in->eof();
        _buf_size = 8;
    }
}
