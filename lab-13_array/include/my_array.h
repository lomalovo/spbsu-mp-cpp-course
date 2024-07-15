#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>
#include <new>

namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:
    T data[N];

    T& at(std::size_t index) {
        if (index >= N) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T at(std::size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of range");
        return data[index];
    }

    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    bool empty() const {
        return N == 0;
    }

    std::size_t size() const {
        return N;
    }

    void fill(const T& val) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = val;
        }
    }

    /*my_array() {
        for (std::size_t i = 0; i < N; ++i) {
            new(&data[i]) T();
        }
    }

    ~my_array() {
        for (std::size_t i = 0; i < N; ++i) {
            data[i].~T();
        }
    }*/
};

class BoolProxy {
        private:
            unsigned char &byte;
            std::size_t bit;

        public:
            BoolProxy(unsigned char &byte, std::size_t bit) : byte(byte), bit(bit) {}

            BoolProxy& operator=(const bool value) {
                if (value) {
                    byte |= (1 << bit);
                } else {
                    byte &= ~(1 << bit);
                }
                return *this;
            }

            BoolProxy& operator=(BoolProxy other) {
                return *this = static_cast<bool>(other);
            }

            operator bool() const {
                return static_cast<bool>((byte >> bit) & 1);
            }
};

template<std::size_t N>
class my_array<bool, N> {
private:
    unsigned char data[(N + 7) / 8];

public:

    bool operator[] (std::size_t index) const {
        std::size_t i = index / 8;
        std::size_t j = index % 8;
        return static_cast<bool>(data[i] & (1 << j));
    }

    BoolProxy operator[] (std::size_t index) {
        return BoolProxy(data[index / 8], index % 8);
    }

    bool at (std::size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of range");
        std::size_t i = index / 8;
        std::size_t j = index % 8;
        return static_cast<bool>(data[i] & (1 << j));
    }

    BoolProxy at (std::size_t index) {
        if (index >= N) throw std::out_of_range("Index out of range");
        return BoolProxy(data[index / 8], index % 8);
    }

    bool empty() const {
        return N == 0;
    }

    std::size_t size() const {
        return N;
    }

    void fill(bool val) {
        for (std::size_t i = 0; i < (N + 7) / 8; ++i) {
            data[i] = val ? 0xFF : 0x00;
        }
    }
};

}  // namespace lab_13

#endif  // MY_ARRAY_H_
