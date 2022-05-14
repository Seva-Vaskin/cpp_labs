#include <fstream>
#include <random>

int main() {
    std::ofstream out("../samples/bigRandomFile.txt", std::ios::binary);
    std::mt19937 rnd(0);
    for (int i = 0; i < 10 * 1024 * 1024; i++) {
        char symbol = char(rnd() % 256);
        out.put(symbol);
    }
    return 0;
}