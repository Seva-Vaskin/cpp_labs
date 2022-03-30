#include "developer.h"

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

    ClassIds Developer::class_id() const {
        return ClassIds::DEVELOPER;
    }

    std::string Developer::position() const {
        return "Developer";
    }

    std::istream &Developer::read_from_istream(std::istream &in) {
        Employee::read_from_istream(in);
        return in >> _has_bonus;
    }

    std::ostream &Developer::write_to_ostream(std::ostream &out) const {
        Employee::write_to_ostream(out);
        return out << "Has bonus: " << (_has_bonus ? '+' : '-') << std::endl;
    }

    std::ifstream &Developer::read_from_ifstream(std::ifstream &in) {
        Employee::read_from_ifstream(in);
        in >> BinManip::read_bool(_has_bonus);
        return in;
    }

    std::ofstream &Developer::write_to_ofstream(std::ofstream &out) const {
        Employee::write_to_ofstream(out);
        out << BinManip::write_bool(_has_bonus);
        return out;
    }

    Developer::Developer() : Employee(), _has_bonus(false) {}

    Developer::Developer(std::ifstream &in) : Developer() {
        Developer::read_from_ifstream(in);
    }

    Developer::Developer(std::istream &in) : Developer() {
        Developer::read_from_istream(in);
    }
}