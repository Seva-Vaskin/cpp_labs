#include "bin_manip.h"


namespace BinManip {
    std::ostream &operator<<(std::ostream &out, const write_le_int32 &data) {
        return out.write(reinterpret_cast<const char *>(&data._x), sizeof data._x);
    }

    std::istream &operator>>(std::istream &in, const read_le_int32 &data) {
        return in.read(reinterpret_cast<char *>(&data._x), sizeof data._x);
    }

    std::ostream &operator<<(std::ostream &out, const write_bool &data) {
        return out.write(reinterpret_cast<const char *>(&data._x), sizeof data._x);
    }

    std::istream &operator>>(std::istream &in, const read_bool &data) {
        return in.read(reinterpret_cast<char *>(&data._x), sizeof data._x);
    }

    std::ostream &operator<<(std::ostream &out, const write_c_str &data) {
        return out.write(data._x, strlen(data._x) * sizeof(char));
    }

    std::istream &operator>>(std::istream &in, const read_c_str &data) {
        in.read(data._x, data._size);
        if (std::count(data._x, data._x + data._size, '\0') == 0)
            throw std::length_error("Not enough space to read the data");
        return in;
    }
}

