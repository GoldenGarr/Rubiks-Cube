#include "Cube.h"
#include <algorithm>

Cube::Cube(const Plane &front, const Plane &back, const Plane &left, const Plane &right, const Plane &upper,
           const Plane &lower) : front_(front), back_(back), left_(left) \
, right_(right), upper_(upper), lower_(lower) {}

Cube::Cube() {
    front_ = Plane(0);
    back_ = Plane(1);
    left_ = Plane(2);
    right_ = Plane(3);
    upper_ = Plane(4);
    lower_ = Plane(5);

//    upper_[0][2] = 100;
//    upper_[2][1] = 69;
}

void Cube::rotate(const std::string &rot) {
    std::cout << "Rotate " + rot << "\n";
    if (rot == "U") {
        /* Upper row
         *    b            l
         * l  o  r  ->  f  o  r
         *    f            b
         * */
        swap_rows(front_, left_, 0, 0);
        swap_rows(front_, back_, 0, 0);
        swap_rows(front_, right_, 0, 0);
        rotate_clockwise(upper_);
    }

    if (rot == "Ui") {
        /* Upper row
         *    b            r
         * l  o  r  ->  b  o  f
         *    f            l
         * */
        swap_rows(front_, right_, 0, 0);
        swap_rows(front_, back_, 0, 0);
        swap_rows(front_, left_, 0, 0);
        rotate_counterclockwise(upper_);
    }

    if (rot == "D") {
//        rotate_clockwise(upper_);
        swap_rows(front_, right_, 2, 2);
        swap_rows(front_, back_, 2, 2);
        swap_rows(front_, left_, 2, 2);
        rotate_clockwise(lower_);
    }

    if (rot == "Di") {
        swap_rows(front_, left_, 2, 2);
        swap_rows(front_, back_, 2, 2);
        swap_rows(front_, right_, 2, 2);

        rotate_counterclockwise(lower_);
    }
}

void Cube::swap_rows(Plane &a, Plane &b, int row_number_a, int row_number_b) {
    for (int i = 0; i < 3; ++i) {
        std::swap(a[row_number_a][i], b[row_number_b][i]);
    }
}

void Cube::rotate_clockwise(Plane &plane) {
    swap_rows(plane, plane, 0, 2);

    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            std::swap(plane[i][j], plane[j][i]);
        }
    }
}

void Cube::rotate_counterclockwise(Plane &plane) {
    for (int i = 0; i < 3; ++i) {
        rotate_clockwise(plane);
    }
}

void Cube::print() {
    std::cout << "Front: \n";
    std::cout << front_;

    std::cout << "Back: \n";
    std::cout << back_;

    std::cout << "Left: \n";
    std::cout << left_;

    std::cout << "Right: \n";
    std::cout << right_;

    std::cout << "Upper: \n";
    std::cout << upper_;

    std::cout << "Lower: \n";
    std::cout << lower_;
}

void Cube::gen_algo_solve(int population_size) {

}

const Plane &Cube::getFront() const {
    return front_;
}

void Cube::setFront(const Plane &front) {
    front_ = front;
}

const Plane &Cube::getBack() const {
    return back_;
}

void Cube::setBack(const Plane &back) {
    back_ = back;
}

const Plane &Cube::getLeft() const {
    return left_;
}

void Cube::setLeft(const Plane &left) {
    left_ = left;
}

const Plane &Cube::getRight() const {
    return right_;
}

void Cube::setRight(const Plane &right) {
    right_ = right;
}

const Plane &Cube::getUpper() const {
    return upper_;
}

void Cube::setUpper(const Plane &upper) {
    upper_ = upper;
}

const Plane &Cube::getLower() const {
    return lower_;
}

void Cube::setLower(const Plane &lower) {
    lower_ = lower;
}


