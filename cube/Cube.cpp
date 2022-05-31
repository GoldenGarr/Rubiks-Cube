#include "Cube.h"

Cube::Cube(const Plane &front, const Plane &back, const Plane &left, const Plane &right, const Plane &upper,
           const Plane &lower) : front_(front), back_(back), left_(left), right_(right), upper_(upper), lower_(lower) {}

Cube::Cube() {}

void Cube::rotate(const std::string &rot) {
    std::cout << "Rotate " + rot << "\n";
    //...
}

void Cube::print() {
    std::cout << front_;
}
