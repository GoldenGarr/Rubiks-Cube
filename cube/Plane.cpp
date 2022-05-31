#include "Plane.h"

Plane::Plane(int color) {
    for (auto &cell: cells_)
        for (int &c: cell)
            c = color;
}

int *Plane::operator[](int index) {
    return cells_[index];
}

std::ostream &operator<<(std::ostream &os, const Plane &plane) {
    for (int i = 1; i <= 9; ++i) {
        os << *plane.cells_[i] << " ";
        if (i % 3 == 0)
            os << "\n";
    }
    return os;
}


