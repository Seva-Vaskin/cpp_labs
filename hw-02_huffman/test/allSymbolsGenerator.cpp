#include <fstream>

int main() {
    std::ofstream out("../samples/allSymbols.txt", std::ios::binary);
    for (int i = 0; i < 256; i++) {
        out << (unsigned char)i;
    }
    return 0;
}