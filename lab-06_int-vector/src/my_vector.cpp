#include "my_vector.hpp"

MyVector::MyVector(size_t init_capacity) {
    _capacity = init_capacity;
    _size = 0;
    _data = new int[_capacity];
}

MyVector::MyVector() : MyVector(2) {}

MyVector::~MyVector() {
    delete[] _data;
}

void MyVector::set(std::size_t index, int value) {
    if (index >= _size)
        throw std::invalid_argument("index out of range");
    _data[index] = value;
}

int MyVector::get(std::size_t index) const {
    if (index >= _size)
        throw std::invalid_argument("index out of range");
    return _data[index];
}

std::size_t MyVector::size() const {
    return _size;
}

std::size_t MyVector::capacity() const {
    return _capacity;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= _capacity)
        return;
    int *new_data = new int[new_capacity];
    std::memcpy(new_data, _data, _size * sizeof(int));
    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
    if (new_size > _capacity)
        reserve(std::max(2 * _capacity, new_size));
    if (new_size > _size)
        std::memset(_data + _size, 0, (new_size - _size) * sizeof(int));
    _size = new_size;
}

void MyVector::push_back(int value) {
    resize(_size + 1);
    _data[_size - 1] = value;
}

void MyVector::insert(std::size_t index, int value) {
    if (index > _size)
        throw std::invalid_argument("index out of range");
    resize(_size + 1);
    std::memmove(_data + index + 1, _data + index, (_size - 1 - index) * sizeof(int));
    _data[index] = value;
}

void MyVector::erase(std::size_t index) {
    if (index >= _size)
        throw std::invalid_argument("index out of range");
    memmove(_data + index, _data + index + 1, (_size - 1 - index) * sizeof(int));
    resize(_size - 1);
}

MyVector::MyVector(const MyVector &other_vector) {
    _size = other_vector._size;
    _capacity = other_vector._capacity;
    _data = new int[_capacity];
    memcpy(_data, other_vector._data, _size * sizeof(int));
}

MyVector &MyVector::operator=(const MyVector &other_vector) {
    if (this == &other_vector)
        return *this;
    resize(other_vector._size);
    std::memcpy(_data, other_vector._data, _size * sizeof(int));
    return *this;
}
