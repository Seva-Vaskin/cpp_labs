#pragma once

#include <cstdint>
#include <string>
#include <cstring>
#include <numeric>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "bin_manip.h"

namespace Employees {

    class Employee {
    public:
        explicit Employee(const char *name, int32_t base_salary);

        virtual ~Employee() = default;

        virtual int32_t salary() const = 0;

        virtual int32_t class_id() const = 0;

        virtual std::string position() const = 0;

        friend std::ostream &operator<<(std::ostream &out, const Employee &employee);

        friend std::istream &operator>>(std::istream &in, Employee &employee);

    protected:
        virtual std::istream &read_from_istream(std::istream &in);

        virtual std::ostream &write_to_ostream(std::ostream &out);

        virtual std::ifstream &read_from_ifstream(std::ifstream &in);

        virtual std::ofstream &write_to_ofstream(std::ofstream &out);

        virtual std::string to_string() const = 0;

    protected:
        static const int _max_name_size = 128;
        char _name[_max_name_size];
        int32_t _base_salary;
    };

    class Developer : public Employee {
    public:
        explicit Developer(const char *name, int32_t base_salary, bool has_bonus);

        int32_t salary() const override;

        int32_t class_id() const override;

        std::string position() const override;

    private:
        std::istream &read_from_istream(std::istream &in) override;

        std::ostream &write_to_ostream(std::ostream &out) override;

        std::ifstream &read_from_ifstream(std::ifstream &in) override;

        std::ofstream &write_to_ofstream(std::ofstream &out) override;

    private:
        bool _has_bonus;
    };

    class SalesManager : public Employee {
    public:
        explicit SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price);

        int32_t salary() const override;

        int32_t class_id() const override;

        std::string position() const override;

    private:
        std::istream &read_from_istream(std::istream &in) override;

        std::ostream &write_to_ostream(std::ostream &out) override;

        std::ifstream &read_from_ifstream(std::ifstream &in) override;

        std::ofstream &write_to_ofstream(std::ofstream &out) override;

    private:
        int32_t _sold_nm, _price;
    };

    class EmployeesArray {
    public:
        void add(Employee *e);

        int32_t total_salary() const;

    private:
        std::vector<Employee *> _employees;
    };
}