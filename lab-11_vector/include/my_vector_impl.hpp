#ifndef MY_VECTOR_IMPL_HPP
#define MY_VECTOR_IMPL_HPP

#include <new>
#include <cassert>
#include <iostream>

std::size_t next_power_of_two(std::size_t n) {
    std::size_t ans = 1;
    while (ans < n) {
        ans *= 2;
    }
    return ans;
}

namespace containers {

template<typename T>
my_vector<T>::my_vector() : capacity_(0), size_(0), array_(nullptr) {}

template<typename T>
my_vector<T>::my_vector(std::size_t n) : capacity_(next_power_of_two(n)), size_(n), array_(static_cast<T*>(::operator new(capacity_ * sizeof(T)))) {
    for(size_t i = 0; i < n; ++i) {
        new (array_ + i) T();
    }
}

template<typename T>
my_vector<T>::my_vector(const my_vector& other) : capacity_(other.capacity_), size_(other.size_), array_(static_cast<T*>(::operator new(other.size_ * sizeof(T)))) {
    for(size_t i = 0; i < other.size_; ++i) {
        new (array_ + i) T(other.array_[i]);
    }
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(my_vector other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(array_, other.array_);
    return *this;
}

template<typename T>
my_vector<T>::~my_vector() {
    clear();
    ::operator delete(array_);
}

template<typename T>
void my_vector<T>::resize(std::size_t n) {
    if (n > capacity_) {
        reserve(n);
    }
    for (size_t i = size_; i < n; ++i) {
        new (array_ + i) T();
    }
    for (size_t i = n; i < size_; ++i) {
        array_[i].~T();
    }
    size_ = n;
}

template<typename T>
void my_vector<T>::reserve(std::size_t n) {
    if (n > capacity_) {
        reallocate(n);
    }
}

template<typename T>
T& my_vector<T>::operator[](std::size_t index) {
    assert(index < size_);
    return array_[index];
}

template<typename T>
const T& my_vector<T>::operator[](std::size_t index) const {
    assert(index < size_);
    return array_[index];
}

template<typename T>
void my_vector<T>::push_back(const T& t) {
    if (size_ >= capacity_) {
        reallocate(capacity_ + 1);
    }
    new (array_ + size_) T(t);
    ++size_;
}

template<typename T>
void my_vector<T>::pop_back() {
    assert(size_ > 0);
    --size_;
    array_[size_].~T();
}

template<typename T>
void my_vector<T>::clear() {
    for (size_t i = 0; i < size_; ++i) {
        array_[i].~T();
    }
    size_ = 0;
}

template<typename T>
void my_vector<T>::reallocate(std::size_t new_cap) {
    new_cap = next_power_of_two(new_cap);
    T* new_array = static_cast<T*>(::operator new(new_cap * sizeof(T)));
    for (size_t i = 0; i < size_; ++i) {
        new (new_array + i) T(std::move(array_[i]));
        array_[i].~T();
    }
    ::operator delete(array_); 
    array_ = new_array;
    capacity_ = new_cap;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& vec) {
    for (std::size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) os << " ";
        os << vec[i];
    }
    return os;

}
}

#endif // MY_VECTOR_IMPL_HPP
