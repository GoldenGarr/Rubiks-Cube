#include "Plane.h"


Plane::Plane() {
    std::string counter = "w";
    for (auto &cell: cells_) {
        for (auto &c: cell) {
            c = counter;
//            ++counter;
        }
    }
}

Plane::Plane(std::string color) {
    for (auto &cell: cells_)
        for (auto &c: cell)
            c = color;
}

Plane& Plane::operator=(const Plane& other) {
    if (this != &other) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                this->cells_[i][j] = other.cells_[i][j];
            }
        }
    }
    return *this;
}


std::string *Plane::operator[](int index) {
    return cells_[index];
}

std::ostream &operator<<(std::ostream &os, const Plane &plane) {
    for (auto cell: plane.cells_) {
        for (int j = 0; j < 3; ++j)
            os << cell[j] << " ";

        os << "\n";
    }
    return os;
}




