#include "Cell.h"

Cell::Cell(int color) : color_(color) {}

int Cell::getColor() const {
    return color_;
}

void Cell::setColor(int color) {
    color_ = color;
}

Cell::Cell() {}
