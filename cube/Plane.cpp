#include "Plane.h"


Plane::Plane() {
    int counter = 0;
    for (auto &cell: cells_) {
        for (int &c: cell) {
            c = counter;
            ++counter;
        }
    }
}

Plane::Plane(int color) {
    for (auto &cell: cells_)
        for (int &c: cell)
            c = color;
//    for (int i = 0; i < ; ++i) {
//
//    }
}

int *Plane::operator[](int index) {
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




