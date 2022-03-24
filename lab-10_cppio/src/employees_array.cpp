#include "employees_array.h"

namespace Employees {
    int32_t EmployeesArray::total_salary() const {
        return std::accumulate(_employees.begin(), _employees.end(), 0,
                               [](int32_t amount, const Employee *employee) {
                                   return amount + employee->salary();
                               });
    }

    void EmployeesArray::add(Employee *e) {
        _employees.push_back(e);
    }

    std::ifstream &operator>>(std::ifstream &in, EmployeesArray &array) {
        int32_t employees_count;
        in >> BinManip::read_le_int32(employees_count);
        for (int32_t i = 0; i < employees_count; i++) {
            array.add_from_ifstream(in);
        }
        return in;
    }

    std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &array) {
        out << BinManip::write_le_int32((int32_t) array._employees.size());
        for (auto employee: array._employees) {
            out << *employee;
        }
        return out;
    }

    std::ostream &operator<<(std::ostream &out, const EmployeesArray &array) {
        for (int32_t i = 0; i < (int32_t) array._employees.size(); i++) {
            out << (i + 1) << ". " << array._employees[i]->position() << std::endl
                << *array._employees[i];
        }
        out << "== Total salary: " << array.total_salary() << std::endl;
        return out;
    }

    std::ifstream &EmployeesArray::add_from_ifstream(std::ifstream &in) {
        int32_t type;
        in >> BinManip::read_le_int32(type);
        Employees::Employee *employee;
        switch (type) {
            case Employees::DEVELOPER:
                employee = new Employees::Developer(in);
                break;
            case Employees::SALES_MANAGER:
                employee = new Employees::SalesManager(in);
                break;
            default:
                throw std::invalid_argument("Broken file");
        }
        add(employee);
        return in;
    }

    std::istream &operator>>(std::istream &in, EmployeesArray &array) {
        int32_t type;
        in >> type;
        Employees::Employee *employee;
        switch (type) {
            case Employees::DEVELOPER:
                employee = new Employees::Developer(in);
                break;
            case Employees::SALES_MANAGER:
                employee = new Employees::SalesManager(in);
                break;
            default:
                throw std::invalid_argument("Broken file");
        }
        array.add(employee);
        return in;
    }

    EmployeesArray::~EmployeesArray() {
        for (auto& i : _employees)
            delete i;
    }
}