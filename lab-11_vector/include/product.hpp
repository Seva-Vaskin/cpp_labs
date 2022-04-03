#pragma once

#include <cstring>
#include <ostream>

namespace product {

    class Product {
    public:
        Product(const char *name, int quantity, double price) {
            size_t name_length = strlen(name);
            name_ = new char[name_length + 1];
            strcpy(name_, name);
            quantity_ = quantity;
            price_ = price;
        }

        Product(const Product &other) : Product(other.name_, other.quantity_, other.price_) {}

        bool operator==(const Product &other) const {
            return strcmp(name_, other.name_) == 0 && quantity_ == other.quantity_ && price_ == other.price_;
        }

        ~Product() {
            delete[] name_;
        }

        friend std::ostream &operator<<(std::ostream &out, const Product &product) {
            return out << product.name_ << ' ' << product.quantity_ << ' ' << product.price_;
        }

    private:
        void swap(Product &other) {
            std::swap(name_, other.name_);
            std::swap(quantity_, other.quantity_);
            std::swap(price_, other.price_);
        }

    private:
        char *name_;
        int quantity_;
        double price_;
    };

}  // namespace product