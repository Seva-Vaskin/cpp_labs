#include <iostream>

#include "my_vector.hpp"
#include <cassert>
#include <string>
#include <sstream>

using containers::my_vector;

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

void test_specification() {
    static_assert(std::is_copy_constructible<my_vector<int>>::value);
    static_assert(std::is_destructible<my_vector<int>>::value);
    static_assert(std::is_copy_constructible<my_vector<product::Product>>::value);
    static_assert(std::is_destructible<my_vector<product::Product>>::value);
    static_assert(!std::is_default_constructible<product::Product>::value);
}

template<typename T>
void do_push_back(my_vector<T> &vec, const T &element) {
    vec.push_back(element);
}

template<typename T, typename... Args>
void do_push_back(my_vector<T> &vec, const T &element, Args... args) {
    vec.push_back(element);
    do_push_back(vec, args...);
}

template<typename T>
void check_equality(const my_vector<T> &vec1, const my_vector<T> &vec2) {
    assert(vec1.size() == vec2.size());
    for (size_t i = 0; i < vec1.size(); i++)
        assert(vec1[i] == vec2[i]);
}

void test_push_back() {
    my_vector<int> vec;
    for (size_t i = 1; i < 10; i++) {
        vec.push_back(int(i));
        assert(vec.size() == i);
        assert(vec.capacity() >= i);
    }
}

void test_empty() {
    my_vector<int> vec;
    assert(vec.empty());
    vec.push_back(1);
    assert(!vec.empty());
}

template<typename T>
void test_copy_constructor(const my_vector<T> &vec) {
    auto vec2 = vec;
    assert(vec2.capacity() == vec.capacity());
    check_equality(vec, vec2);
}

template<typename T>
void test_default_constructor() {
    my_vector<T> vec;
    assert(vec.capacity() == 2);
    assert(vec.size() == 0);
}

template<typename T>
void test_pop_back(my_vector<T> vec) {
    size_t size = vec.size();
    for (size_t i = 0; i < size; i++)
        vec.pop_back();
    assert(vec.empty());
}

template<typename T>
void test_assignment_operator(const my_vector<T> &vec) {
    my_vector<T> vec2;
    vec2 = vec;
    check_equality(vec, vec2);
}

void test_output() {
    my_vector<int> vec;
    for (int i = 0; i < 5; i++)
        vec.push_back(i);
    std::string expected = "0 1 2 3 4";
    std::stringstream stream;
    stream << vec;
    std::string actual = stream.str();
    assert(actual == expected);
}

template<typename T>
void test_clear(my_vector<T> vec) {
    vec.clear();
    assert(vec.empty());
}


template<typename T, typename... Args>
void test_my_vector(Args... args) {
    test_specification();
    test_push_back();
    test_empty();
    test_default_constructor<int>();
    test_default_constructor<product::Product>();
    test_output();

    my_vector<T> vec;
    do_push_back(vec, args...);

    test_copy_constructor(vec);
    test_assignment_operator(vec);
    test_pop_back(vec);
    test_clear(vec);
}

template<typename T>
void test_resize_decrease(const my_vector<T> &vec) {
    my_vector<T> vec2 = vec;
    size_t new_size = vec.size() / 2;
    vec2.resize(new_size);
    assert(vec2.size() == new_size);
    for (size_t i = 0; i < new_size; i++)
        assert(vec2[i] == vec[i]);
}

template<typename T>
void test_resize_increase(const my_vector<T> &vec) {
    my_vector<T> vec2 = vec;
    size_t new_size = vec.size() * 2;
    vec2.resize(new_size);
    assert(vec2.size() == new_size);
    for (size_t i = 0; i < vec.size(); i++)
        assert(vec2[i] == vec[i]);
    T default_value = T();
    for (size_t i = vec.size(); i < new_size; i++)
        assert(vec2[i] == default_value);
}

template<typename T>
void test_constructor_by_size() {
    size_t size = 5;
    my_vector<T> vec(size);
    assert(vec.size() == size);
    T default_value = T();
    for (size_t i = 0; i < size; i++)
        assert(vec[i] == default_value);
}

template<typename T, typename... Args>
void test_my_vector_default_constructible(Args... args) {
    my_vector<T> vec;
    do_push_back(vec, args...);

    test_constructor_by_size<T>();
    test_resize_decrease(vec);
    test_resize_increase(vec);
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<product::Product>(
            product::Product("asdf", 4, 12.0),
            product::Product("qwe", -1, 7.5)
    );

    test_my_vector_default_constructible<int>(5, 10);

    std::cout << "finished\n";

    return 0;
}
