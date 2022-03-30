#pragma once

#include <vector>
#include <numeric>

#include "employee.h"
#include "bin_manip.h"

namespace Employees {
    class SalesManager : public Employee {
    public:
        explicit SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price);

        explicit SalesManager(std::ifstream &in);

        explicit SalesManager(std::istream &in);

        int32_t salary() const override;

        ClassIds class_id() const override;

        std::string position() const override;

    private:
        explicit SalesManager();

        std::istream &read_from_istream(std::istream &in) override;

        std::ostream &write_to_ostream(std::ostream &out) const override;

        std::ifstream &read_from_ifstream(std::ifstream &in) override;

        std::ofstream &write_to_ofstream(std::ofstream &out) const override;

    private:
        int32_t _sold_nm, _price;
    };
}