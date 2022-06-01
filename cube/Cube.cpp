#include "Cube.h"
#include <algorithm>

Cube::Cube(const Plane &front, const Plane &back, const Plane &left, const Plane &right, const Plane &upper,
           const Plane &lower) : front_(front), back_(back), left_(left) \
, right_(right), upper_(upper), down_(lower) {}

Cube::Cube() {
    front_ = Plane(0);
    back_ = Plane(1);
    left_ = Plane(2);
    right_ = Plane(3);
    upper_ = Plane(4);
    down_ = Plane(5);

//    upper_[0][2] = 100;
//    upper_[2][1] = 69;
}

void Cube::rotate(const std::string &rot) {
    std::cout << "Rotate " + rot << "\n";
    if (rot == "U") {
        /* Upper row
         *    b            l
         * l  o  r  ->  f  o  b
         *    f            r
         * + Rotate the upper plane clockwise
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
         * + Rotate the upper plane counterclockwise
         * */
        swap_rows(front_, right_, 0, 0);
        swap_rows(front_, back_, 0, 0);
        swap_rows(front_, left_, 0, 0);
        rotate_counterclockwise(upper_);
    }

    if (rot == "D") {
        /* Lower row
         *    b            r
         * l  o  r  ->  b  o  f
         *    f            l
         * + Rotate the upper plane clockwise
         * */
        swap_rows(front_, right_, 2, 2);
        swap_rows(front_, back_, 2, 2);
        swap_rows(front_, left_, 2, 2);
        rotate_clockwise(down_);
    }

    if (rot == "Di") {
        /* Lower row
         *    b            l
         * l  o  r  ->  f  o  b
         *    f            r
         * + Rotate the lower plane counterclockwise
         * */
        swap_rows(front_, left_, 2, 2);
        swap_rows(front_, back_, 2, 2);
        swap_rows(front_, right_, 2, 2);
        rotate_counterclockwise(down_);
    }

    if (rot == "R") {
        swap_columns(front_, upper_, 2, 2);
        swap_columns(front_, back_, 2, 2);
        swap_columns(front_, down_, 2, 2);
        rotate_clockwise(right_);
    }

    if (rot == "Ri") {
        swap_columns(front_, down_, 2, 2);
        swap_columns(front_, back_, 2, 2);
        swap_columns(front_, upper_, 2, 2);
        rotate_counterclockwise(right_);
    }

    if (rot == "L") {
        swap_columns(front_, down_, 0, 0);
        swap_columns(front_, back_, 0, 0);
        swap_columns(front_, upper_, 0, 0);
        rotate_clockwise(left_);
    }

    if (rot == "Li") {
        swap_columns(front_, upper_, 0, 0);
        swap_columns(front_, back_, 0, 0);
        swap_columns(front_, down_, 0, 0);
        rotate_counterclockwise(left_);
    }

    if (rot == "F") {
        swap_row_column(upper_, right_, 2, 0);
        swap_row_column(upper_, left_, 2, 2);
        swap_row_column(down_, left_, 0, 2);

        rotate_clockwise(front_);
    }
}

void Cube::swap_rows(Plane &a, Plane &b, int row_number_a, int row_number_b) {
    for (int i = 0; i < 3; ++i) {
        std::swap(a[row_number_a][i], b[row_number_b][i]);
    }
}

void Cube::swap_columns(Plane &a, Plane &b, int column_number_a, int column_number_b) {
    for (int i = 0; i < 3; ++i) {
        std::swap(a[i][column_number_a], b[i][column_number_b]);
    }
}

void Cube::swap_row_column(Plane& row_plane, Plane& column_plane, int row_number, int column_number) {
    for (int i = 0; i < 3; ++i) {
        std::swap(row_plane[row_number][i], column_plane[i][column_number]);
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
    std::cout << "Front 0 : \n";
    std::cout << front_;

    std::cout << "Back 1 : \n";
    std::cout << back_;

    std::cout << "Left 2 : \n";
    std::cout << left_;

    std::cout << "Right 3 : \n";
    std::cout << right_;

    std::cout << "Upper 4 : \n";
    std::cout << upper_;

    std::cout << "Lower 5 : \n";
    std::cout << down_;
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
    return down_;
}

void Cube::setLower(const Plane &lower) {
    down_ = lower;
}


