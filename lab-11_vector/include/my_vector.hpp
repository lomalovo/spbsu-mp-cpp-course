#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef> 
#include <algorithm> 
#include <utility> 

namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();
    explicit my_vector(std::size_t n);
    my_vector(const my_vector& other);
    my_vector& operator=(my_vector other);
    ~my_vector();

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    void push_back(const T& t);
    void pop_back();
    void clear();

private:
    std::size_t capacity_ = 0;
    std::size_t size_ = 0;
    T* array_ = nullptr;

    void reallocate(std::size_t new_cap);
};

}

#include "my_vector_impl.hpp"

#endif // MY_VECTOR_H_
