#include "employees.h"

namespace Employees {

    int32_t Developer::salary() const {
        int32_t salary = _base_salary;
        if (_has_bonus) {
            salary += 1000;
        }
        return salary;
    }

    Developer::Developer(const char *name, int32_t base_salary, bool has_bonus) : Employee(name, base_salary),
                                                                                  _has_bonus(has_bonus) {}

    int32_t Developer::class_id() const {
        return 1;
    }

    std::istream &Developer::read_from_istream(std::istream &in) {
        Employee::read_from_istream(in);
        return in >> _has_bonus;
    }

    std::string Developer::position() const {
        return "Developer";
    }

    int32_t SalesManager::salary() const {
        return _base_salary + _sold_nm * _price / 100;
    }

    SalesManager::SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price) :
            Employee(name, base_salary), _sold_nm(sold_nm), _price(price) {}

    int32_t SalesManager::class_id() const {
        return 2;
    }

    std::istream &SalesManager::read_from_istream(std::istream &in) {
        Employee::read_from_istream(in);
        return in >> _sold_nm >> _price;
    }

    std::string SalesManager::position() const {
        return "Sales Manager";
    }

    int32_t EmployeesArray::total_salary() const {
        return std::accumulate(_employees.begin(), _employees.end(), 0,
                               [](int32_t amount, const Employee *employee) {
                                   return amount + employee->salary();
                               });
    }

    void EmployeesArray::add(Employee *e) {
        _employees.push_back(e);
    }

    Employee::Employee(const char *name, int32_t base_salary) : _base_salary(base_salary) {
        if (strlen(name) >= _max_name_size)
            throw std::length_error("Too large name");
        strcpy(_name, name);
    }

    std::ostream &operator<<(std::ostream &out, const Employee &employee) {
        return out << employee.to_string();
    }

    std::istream &operator>>(std::istream &in, Employee &employee) {
        return employee.read_from_istream(in);
    }

    std::istream &Employee::read_from_istream(std::istream &in) {
        return in >> _name >> _base_salary;
    }

    std::ifstream &Employee::read_from_ifstream(std::ifstream &in) {
        in >> BinManip::read_c_str(_name, _max_name_size * sizeof(char))
           >> BinManip::read_le_int32(_base_salary);
        return in;
    }

}