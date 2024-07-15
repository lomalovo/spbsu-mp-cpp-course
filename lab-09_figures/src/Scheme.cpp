#include "Scheme.hpp"
#include <iostream>

Scheme::Scheme(int capacity) : capacity_(capacity), size_(0) {
    figures_ = new Figure*[capacity_];
}

Scheme::~Scheme() {
    for (int i = 0; i < size_; ++i) {
        delete figures_[i];
    }
    delete[] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
    if (size_ < capacity_) {
        figures_[size_++] = fg;
    }
}

void Scheme::remove_figure(int id) {
    for (int i = 0; i < size_; ++i) {
        if (figures_[i]->get_id() == id) {
            delete figures_[i];
            for (int j = i; j < size_ - 1; ++j) {
                figures_[j] = figures_[j + 1];
            }
            --size_;
            break;
        }
    }
}

void Scheme::print_all_figures() {
    for (int i = 0; i < size_; ++i) {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    for (int i = 0; i < size_; ++i) {
        if (figures_[i]->get_id() == id) {
            figures_[i]->zoom(factor);
            break;
        }
    }
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < size_; ++i) {
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    for (int i = 0; i < size_; ++i) {
        if (figures_[i]->get_id() == id) {
            figures_[i]->move(new_x, new_y);
            break;
        }
    }
}
