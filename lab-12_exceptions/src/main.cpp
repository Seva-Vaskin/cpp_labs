#include <iostream>
#include <string>

#include "registers.h"

int main() {
    matrix::Registers registers;

    std::string cmd;
    while (std::cin >> cmd) {
        try {
            if (cmd == "exit") {
                break;
            } else if (cmd == "load") {
                std::string str_id, filename;
                std::cin >> str_id >> filename;
                registers.load(str_id, filename);
            } else if (cmd == "print") {
                std::string str_id;
                std::cin >> str_id;
                registers.print(str_id);
            } else if (cmd == "add") {
                std::string str_id1, str_id2;
                std::cin >> str_id1 >> str_id2;
                registers.add(str_id1, str_id2);
            } else if (cmd == "mul") {
                std::string str_id1, str_id2;
                std::cin >> str_id1 >> str_id2;
                registers.mul(str_id1, str_id2);
            } else if (cmd == "elem") {
                std::string str_id;
                size_t row, col;
                std::cin >> str_id >> row >> col;
                std::cout << registers.elem(str_id, row, col) << std::endl;
            } else {
                std::cout << "Undefined command" << std::endl;
            }
        } catch (const std::exception &exception) {
            std::cout << exception.what() << std::endl;
        }
    }
    return 0;
}