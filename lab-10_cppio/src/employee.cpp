#include "employee.h"

namespace Employees {
    Employee::Employee(const char *name, int32_t base_salary) : _name(nullptr), _base_salary(base_salary) {
        set_name(name);
    }

    Employee::Employee() : _name(nullptr), _base_salary(0) {}

    Employee::~Employee() {
        delete[] _name;
    }

    std::ostream &operator<<(std::ostream &out, const Employee &employee) {
        return employee.write_to_ostream(out);
    }

    std::istream &operator>>(std::istream &in, Employee &employee) {
        return employee.read_from_istream(in);
    }

    std::ofstream &operator<<(std::ofstream &out, const Employee &employee) {
        return employee.write_to_ofstream(out);
    }

    std::ifstream &operator>>(std::ifstream &in, Employee &employee) {
        return employee.read_from_ifstream(in);
    }

    std::istream &Employee::read_from_istream(std::istream &in) {
        char name[_max_name_size + 1];
        in >> name >> _base_salary;
        set_name(name);
        return in;
    }

    std::ifstream &Employee::read_from_ifstream(std::ifstream &in) {
        char buf[_max_name_size + 1];
        in >> BinManip::read_c_str(buf, _max_name_size * sizeof(char))
           >> BinManip::read_le_int32(_base_salary);
        set_name(buf);
        return in;
    }

    std::ostream &Employee::write_to_ostream(std::ostream &out) const {
        out << "Name: " << _name << std::endl
            << "Base Salary: " << _base_salary << std::endl;
        return out;
    }

    std::ofstream &Employee::write_to_ofstream(std::ofstream &out) const {
        out << BinManip::write_le_int32(class_id())
            << BinManip::write_c_str(_name)
            << BinManip::write_le_int32(_base_salary);
        return out;
    }

    void Employee::set_name(const char *new_name) {
        size_t name_len = strlen(new_name);
        if (name_len > _max_name_size)
            throw std::length_error("Too long name");
        delete[] _name;
        _name = new char[name_len + 1];
        strcpy(_name, new_name);
    }
}