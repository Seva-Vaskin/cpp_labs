#include <iostream>

#include "employees_array.h"

int main() {

    Employees::EmployeesArray array;

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "exit") {
            break;
        } else if (cmd == "load") {
            std::string file_name;
            std::cin >> file_name;
            std::ifstream file(file_name, std::ios::binary | std::ios::in);
            file >> array;
            file.close();
        } else if (cmd == "save") {
            std::string file_name;
            std::cin >> file_name;
            std::ofstream file(file_name, std::ios::binary | std::ios::out);
            file << array;
            file.close();
        } else if (cmd == "list") {
            std::cout << array << std::endl;
        } else if (cmd == "add") {
            std::cin >> array;
        } else {
            std::cout << "Undefined command: " << cmd << std::endl;
        }
    }
    return 0;
}