#include "sales_manager.h"

namespace Employees {

    int32_t SalesManager::salary() const {
        return _base_salary + _sold_nm * _price / 100;
    }

    SalesManager::SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price) :
            Employee(name, base_salary), _sold_nm(sold_nm), _price(price) {}

    ClassIds SalesManager::class_id() const {
        return ClassIds::SALES_MANAGER;
    }

    std::istream &SalesManager::read_from_istream(std::istream &in) {
        Employee::read_from_istream(in);
        return in >> _sold_nm >> _price;
    }

    std::string SalesManager::position() const {
        return "Sales Manager";
    }

    std::ostream &SalesManager::write_to_ostream(std::ostream &out) const {
        Employee::write_to_ostream(out);
        return out << "Sold items: " << _sold_nm << std::endl
                   << "Item price: " << _price << std::endl;
    }

    std::ifstream &SalesManager::read_from_ifstream(std::ifstream &in) {
        Employee::read_from_ifstream(in);
        in >> BinManip::read_le_int32(_sold_nm) >> BinManip::read_le_int32(_price);
        return in;
    }

    std::ofstream &SalesManager::write_to_ofstream(std::ofstream &out) const {
        Employee::write_to_ofstream(out);
        out << BinManip::write_le_int32(_sold_nm) << BinManip::write_le_int32(_price);
        return out;
    }

    SalesManager::SalesManager() : Employee(), _sold_nm(0), _price(0) {}

    SalesManager::SalesManager(std::ifstream &in) : SalesManager() {
        SalesManager::read_from_ifstream(in);
    }

    SalesManager::SalesManager(std::istream &in) : SalesManager() {
        SalesManager::read_from_istream(in);
    }
}