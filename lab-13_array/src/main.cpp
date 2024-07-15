#include "my_array.h"
#include <iostream>

int main() {
    std::cout << "Test my_array<int, 5>:" << std::endl;
    lab_13::my_array<int, 5> arr_int;
    arr_int.fill(42);

    for (std::size_t i = 0; i < arr_int.size(); ++i) {
        std::cout << "arr_int[" << i << "] = " << arr_int[i] << std::endl;
    }

    std::cout << "\nTest my_array<bool, 10>:" << std::endl;
    lab_13::my_array<bool, 10> arr_bool;
    arr_bool.fill(true);

    for (std::size_t i = 0; i < arr_bool.size(); ++i) {
        std::cout << "arr_bool[" << i << "] = " << arr_bool[i] << std::endl;
    }

    arr_bool[2] = false;
    std::cout << "arr_bool[2] = " << arr_bool[2] << std::endl;

    return 0;
}
