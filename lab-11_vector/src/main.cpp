#include <iostream>
#include "my_vector.hpp"
#include <cstring>

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price) : quantity_(quantity), price_(price) {
        name_ = new char[strlen(name) + 1];
        strcpy(name_, name);
    }
    Product(const Product& other) : quantity_(other.quantity_), price_(other.price_) {
        name_ = new char[strlen(other.name_) + 1];
        strcpy(name_, other.name_);
    }
    Product& operator=(const Product& other) {
        if (this != &other) {
            delete[] name_;
            name_ = new char[strlen(other.name_) + 1];
            strcpy(name_, other.name_);
            quantity_ = other.quantity_;
            price_ = other.price_;
        }
        return *this;
    }
    ~Product() {
        delete[] name_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        return os << product.name_ << ' ' << product.quantity_ << ' ' << product.price_;
    }

private:
    char* name_;
    int quantity_;
    double price_;
};

} 

using namespace containers;
using namespace product;

int main() {
    my_vector<int> int_vector;
    int_vector.push_back(10);
    int_vector.push_back(20);
    std::cout << "Int vector: ";
    for (size_t i = 0; i < int_vector.size(); ++i) {
        std::cout << int_vector[i] << ' ';
    }
    std::cout << '\n';

    my_vector<Product> product_vector;
    product_vector.push_back(Product("Apple", 10, 0.99));
    product_vector.push_back(Product("Banana", 20, 0.59));
    std::cout << "Product vector: ";
    for (size_t i = 0; i < product_vector.size(); ++i) {
        std::cout << product_vector[i] << "; ";
    }
    std::cout << '\n';

    return 0;
}
