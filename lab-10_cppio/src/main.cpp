#include "employees.h"
#include "bin_manip.h"

#include <sstream>

using BinManip::write_le_int32;
using BinManip::read_le_int32;

int main() {

    std::stringstream s;
    int x = 10;
    s << write_le_int32(x);  // Теперь в s лежит четыре байта: 0A 00 00 00.
    s >> read_le_int32(x);  // Обратная операция: присваивает x = 10.
    s.write("\x12\x34\x56\0", 4);
    s >> read_le_int32(x);  // x = 0x00563412 = 5649426

    return 0;
}