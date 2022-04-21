#pragma once

#include <cstddef>
#include <ostream>

namespace containers {

    template<typename T>
    class my_vector {
    public:
        my_vector() {
            capacity_ = 1;
            size_ = 0;
            array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
        }

        explicit my_vector(std::size_t n) : capacity_(1), size_(0), array_(nullptr) {
            static_assert(std::is_default_constructible<T>::value);
            reserve(n);
            for (size_t i = 0; i < n; i++)
                new(array_ + i) T();
            size_ = n;
        }

        explicit my_vector(std::size_t n, const T &init_value) : capacity_(1), size_(0), array_(nullptr) {
            static_assert(std::is_copy_constructible<T>::value);
            reserve(n);
            size_ = n;
            for (size_t i = 0; i < n; i++) {
                new(array_ + i) T(init_value);
            }
        }

        my_vector(const my_vector &other) {
            static_assert(std::is_copy_constructible<T>::value);
            capacity_ = other.capacity_;
            size_ = other.size_;
            array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
            for (size_t i = 0; i < size_; i++) {
                new(array_ + i) T(other[i]);
            }
        }

        my_vector &operator=(const my_vector &other) {
            if (this == &other)
                return *this;
            my_vector<T> tmp = other;
            swap(tmp);
            return *this;
        }

        ~my_vector() {
            for (size_t i = 0; i < size_; i++) {
                array_[i].~T();
            }
            delete[] reinterpret_cast<char *>(array_);
        }

        size_t size() const {
            return size_;
        }

        size_t capacity() const {
            return capacity_;
        }

        bool empty() const {
            return size_ == 0;
        }

        void resize(std::size_t n) {
            static_assert(std::is_default_constructible<T>::value);
            while (size_ > n)
                array_[--size_].~T();
            reserve(n);
            while (size_ < n)
                new(array_ + (size_++)) T();
        }

        void reserve(std::size_t n) {
            if (n <= capacity_)
                return;
            size_t new_capacity = capacity_;
            while (new_capacity < n)
                new_capacity <<= 1;
            T *new_array = reinterpret_cast<T *>(new char[sizeof(T) * new_capacity]);
            for (size_t i = 0; i < size_; i++) {
                new(new_array + i) T(array_[i]);
                array_[i].~T();
            }
            delete[] reinterpret_cast<char *>(array_);
            array_ = reinterpret_cast<T *>(new_array);
            capacity_ = new_capacity;
        }

        T &operator[](std::size_t index) {
            return array_[index];
        }

        const T &operator[](std::size_t index) const {
            return array_[index];
        }

        void push_back(const T &t) {
            reserve(size_ + 1);
            new(array_ + size_) T(t);
            size_++;
        }

        void pop_back() {
            size_--;
            array_[size_].~T();
        }

        void clear() {
            for (size_t i = 0; i < size_; i++)
                array_[i].~T();
            size_ = 0;
        }

        friend std::ostream &operator<<(std::ostream &out, const my_vector &my_vec) {
            for (size_t i = 0; i < my_vec.size_; i++) {
                out << my_vec[i];
                if (i + 1 < my_vec.size_)
                    out << ' ';
            }
            return out;
        }

    private:
        void swap(my_vector &other) {
            std::swap(capacity_, other.capacity_);
            std::swap(size_, other.size_);
            std::swap(array_, other.array_);
        }

    private:
        size_t capacity_;
        size_t size_;
        T *array_;
    };

}
