#pragma once

#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstring>
#include "bin_manip.h"

namespace Employees {

    enum ClassIds {
        DEVELOPER = 1,
        SALES_MANAGER = 2
    };

    class Employee {
    public:
        explicit Employee(const char *name, int32_t base_salary);

        virtual ~Employee();

        virtual int32_t salary() const = 0;

        virtual ClassIds class_id() const = 0;

        virtual std::string position() const = 0;

        friend std::ostream &operator<<(std::ostream &out, const Employee &employee);

        friend std::istream &operator>>(std::istream &in, Employee &employee);

        friend std::ofstream &operator<<(std::ofstream &out, const Employee &employee);

        friend std::ifstream &operator >>(std::ifstream &in, Employee &employee);
    protected:
        explicit Employee();

        virtual std::istream &read_from_istream(std::istream &in);

        virtual std::ostream &write_to_ostream(std::ostream &out) const;

        virtual std::ifstream &read_from_ifstream(std::ifstream &in);

        virtual std::ofstream &write_to_ofstream(std::ofstream &out) const;

        void set_name(const char *new_name);

    public:
        static const int _max_name_size = 127;

    protected:
        char *_name;
        int32_t _base_salary;
    };
}