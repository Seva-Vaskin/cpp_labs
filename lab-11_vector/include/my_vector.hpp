#pragma once

#include <cstddef>

namespace containers {

    template<typename T>
    class my_vector {
    public:
        my_vector() {
            capacity_ = 2;
            size_ = 0;
            array_ = new char[sizeof(T) * capacity_];
        }

        explicit my_vector(std::size_t n) : my_vector() {
            static_assert(std::is_default_constructible<T>::value);
            reserve(n);
            size_ = n;
            array_ = new T[n];
        }

        explicit my_vector(std::size_t n, const T& default_value) : my_vector() {

        }

        my_vector(my_vector other);

        my_vector operator=(my_vector other);

        ~my_vector();

        std::size_t size();

        std::size_t capacity();

        bool empty();

        void resize(std::size_t n);

        void reserve(std::size_t n);

        ??

        operator[](std::size_t index);

        void push_back(T t);

        void pop_back();

        void clear();

    private:
        size_t capacity_{};
        size_t size_;
        T *array_;
    };

}