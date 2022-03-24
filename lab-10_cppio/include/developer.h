#pragma once

#include "employee.h"

namespace Employees {
    class Developer : public Employee {
    public:
        explicit Developer(const char *name, int32_t base_salary, bool has_bonus);

        explicit Developer(std::ifstream &in);

        explicit Developer(std::istream &in);

        int32_t salary() const override;

        ClassIds class_id() const override;

        std::string position() const override;

    private:
        explicit Developer();

        std::istream &read_from_istream(std::istream &in) override;

        std::ostream &write_to_ostream(std::ostream &out) const override;

        std::ifstream &read_from_ifstream(std::ifstream &in) override;

        std::ofstream &write_to_ofstream(std::ofstream &out) const override;

    private:
        bool _has_bonus;
    };
}