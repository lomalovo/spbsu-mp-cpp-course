#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(int id, int x, int y, int width, int height)
        : Figure(id, x, y), width(width), height(height) {}

Rectangle::~Rectangle() = default;

void Rectangle::print() const {
    std::cout << "Rectangle " << id << ": x = " << x << " y = " << y
              << " width = " << width << " height = " << height << std::endl;
}

bool Rectangle::is_inside(int px, int py) const {
    return (px >= x - width / 2 && px <= x + width / 2 && py >= y - height / 2 && py <= y + height / 2);
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}
