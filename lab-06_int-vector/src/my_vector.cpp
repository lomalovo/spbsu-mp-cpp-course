#include <utility>
#include "my_vector.hpp"


MyVector::MyVector() : MyVector(2) {};

MyVector::MyVector(std::size_t init_capacity) {
    _size = 0;
    _capacity = init_capacity >= 1 ? init_capacity : 1;
    _data = new int[init_capacity];
};

MyVector::~MyVector() {
    delete [] _data;
};

MyVector::MyVector(const MyVector &other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new int[other._capacity];

    for (std::size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

MyVector& MyVector::operator=(MyVector other) {
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_data, other._data);

    return *this;
};

void MyVector::set(std::size_t index, int value) {
    while (index + 1 > _capacity) {
        reserve(_capacity * 2);
    }

    _data[index] = value;
};

int MyVector::get(std::size_t index) {
    return _data[index];
};

std::size_t MyVector::size() {
    return _size;
};

std::size_t MyVector::capacity() {
    return _capacity;
};

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= _capacity) {
        return;
    }

    MyVector new_vector = MyVector(new_capacity);
    std::swap(_data, new_vector._data);
    std::swap(_capacity, new_vector._capacity);

    for (std::size_t i = 0; i<_size; i++) {
        _data[i] = new_vector._data[i];
    }
};

void MyVector::resize(std::size_t new_size) {
    if (new_size > _capacity) {
        reserve(new_size > (2 * _capacity) ? new_size : (2 * _capacity));
    }
    
    for (std::size_t i = _size; i < new_size; i++) {
        set(i, 0);
    }

    _size = new_size;
};

void MyVector::push_back(int value) {
    set(_size, value);
    _size += 1;
};

void MyVector::insert(std::size_t index, int value) {
    push_back(value);

    if (_size == 0) {
        return;
    }

    for (std::size_t i=_size-1; i > index; i--) {
        set(i, get(i-1));
    }

    set(index, value);

};

void MyVector::erase(std::size_t index) {
    if (index+1 > _size) {
        return;
    }

    for (std::size_t i = index; i + 1 < _size; i++) {
        set(i, get(i+1));
    }
    
    _size -= 1;
};