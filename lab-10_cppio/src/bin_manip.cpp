#include "bin_manip.h"


namespace BinManip {
    std::ostream &operator<<(std::ostream &out, const write_le_int32 &data) {
        uint8_t buf[4];
        for (uint32_t i = 0; i < 4; i++) {
            buf[i] = data._x >> (8u * i) & 255;
        }
        return out.write(reinterpret_cast<const char *>(buf), sizeof buf);
    }

    std::istream &operator>>(std::istream &in, const read_le_int32 &data) {
        uint8_t buf[4];
        in.read(reinterpret_cast<char *>(buf), sizeof buf);
        data._x = 0;
        for (int32_t i = 3; i >= 0; i--)
            data._x = data._x * 256 + buf[i];
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const write_bool &data) {
        return out.write(reinterpret_cast<const char *>(&data._x), sizeof data._x);
    }

    std::istream &operator>>(std::istream &in, const read_bool &data) {
        return in.read(reinterpret_cast<char *>(&data._x), sizeof data._x);
    }

    std::ostream &operator<<(std::ostream &out, const write_c_str &data) {
        return out.write(data._x, (strlen(data._x) + 1) * sizeof(char));
    }

    std::istream &operator>>(std::istream &in, const read_c_str &data) {
        for (int32_t i = 0; i < (int32_t) data._size; i++) {
            in.read(data._x + i, sizeof(char));
            if (data._x[i] == '\0')
                return in;
        }
        throw std::length_error("Not enough space to read the data");
    }
}

