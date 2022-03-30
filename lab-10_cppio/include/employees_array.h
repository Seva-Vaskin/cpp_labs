#pragma once

#include <vector>
#include <numeric>

#include "employee.h"
#include "developer.h"
#include "sales_manager.h"

namespace Employees {
    class EmployeesArray {
    public:
        EmployeesArray() = default;

        ~EmployeesArray();

        void add(Employee *e);

        int32_t total_salary() const;

        std::ifstream &add_from_ifstream(std::ifstream& in);

        friend std::ifstream &operator>>(std::ifstream &in, EmployeesArray &array);

        friend std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &array);

        friend std::ostream &operator<<(std::ostream &out, const EmployeesArray &array);

        friend std::istream &operator>>(std::istream &in, EmployeesArray &array);
    private:
        std::vector<Employee *> _employees;
    };
}