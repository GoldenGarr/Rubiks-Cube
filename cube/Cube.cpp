#include "Cube.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <utility>

Cube::Cube(Plane front, Plane back, Plane left, Plane right, Plane upper,
           Plane lower) : front_(std::move(front)), back_(std::move(back)), left_(std::move(left)) \
, right_(std::move(right)), upper_(std::move(upper)), down_(std::move(lower)) {}

Cube::Cube() {
    front_ = Plane("r");
    back_ = Plane("o");
    left_ = Plane("g");
    right_ = Plane("b");
    upper_ = Plane("w");
    down_ = Plane("y");
}

// Required sequence: Front -> Back -> Left -> Right -> Upper -> Down
Cube Cube::read_file(const char *path) {
    Cube cube;
    std::ifstream file(path);
    if (file.is_open()) {
        assign_cells(cube.front_, file);
        assign_cells(cube.back_, file);
        assign_cells(cube.left_, file);
        assign_cells(cube.right_, file);
        assign_cells(cube.upper_, file);
        assign_cells(cube.down_, file);
    }
    return cube;
}

// Output sequence: Front -> Back -> Left -> Right -> Upper -> Down
void Cube::to_txt(const std::string &name) {
    std::ofstream file(name + ".txt");
    if (file.is_open()) {
        file << front_ << back_ << left_ << right_
             << upper_ << down_;
        file.close();
    }
}

void Cube::assign_cells(Plane &plane, std::ifstream &is) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            is >> plane[i][j];
        }
    }
}

Cube Cube::generate_random(int n_complexity) {
    std::string rotations[12] = {"U", "Ui", "D", "Di", "R", "Ri",
                                 "L", "Li", "F", "Fi", "B", "Bi"};
    Cube cube = Cube();
    for (int i = 0; i < n_complexity; ++i)
        cube.rotate(rotations[rand() % 12]);

    return cube;
}


// 12 basic cube rotations
void Cube::rotate(const std::string &rot) {
//    std::cout << "Rotate " + rot << "\n";
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
        swap_columns(front_, back_, 2, 0);
        swap_columns(front_, down_, 2, 2);
        std::swap(back_[0][0], back_[2][0]);
        std::swap(down_[0][2], down_[2][2]);
        rotate_clockwise(right_);
    }

    if (rot == "Ri") {
        swap_columns(front_, down_, 2, 2);
        swap_columns(front_, back_, 2, 0);
        swap_columns(front_, upper_, 2, 2);
        std::swap(back_[0][0], back_[2][0]);
        std::swap(upper_[0][2], upper_[2][2]);
        rotate_counterclockwise(right_);
    }

    if (rot == "L") {
        swap_columns(front_, down_, 0, 0);
        swap_columns(front_, back_, 0, 2);
        swap_columns(front_, upper_, 0, 0);
        std::swap(back_[0][2], back_[2][2]);
        std::swap(upper_[0][0], upper_[2][0]);
        rotate_clockwise(left_);
    }

    if (rot == "Li") {
        swap_columns(front_, upper_, 0, 0);
        swap_columns(front_, back_, 0, 2);
        swap_columns(front_, down_, 0, 0);
        std::swap(back_[0][2], back_[2][2]);
        std::swap(down_[0][0], down_[2][0]);
        rotate_counterclockwise(left_);
    }

    if (rot == "F") {
        swap_row_column(upper_, right_, 2, 0);
        swap_row_column(upper_, left_, 2, 2);
        swap_row_column(down_, left_, 0, 2);
        std::swap(upper_[2][0], upper_[2][2]);
        std::swap(down_[0][0], down_[0][2]);
        rotate_clockwise(front_);
    }

    if (rot == "Fi") {
        swap_row_column(down_, left_, 0, 2);
        swap_row_column(upper_, left_, 2, 2);
        swap_row_column(upper_, right_, 2, 0);
        std::swap(left_[0][2], left_[2][2]);
        std::swap(right_[0][0], right_[2][0]);
        rotate_counterclockwise(front_);
    }

    if (rot == "B") {
        swap_row_column(down_, left_, 2, 0);
        swap_row_column(upper_, left_, 0, 0);
        swap_row_column(upper_, right_, 0, 2);
        std::swap(left_[0][0], left_[2][0]);
        std::swap(right_[0][2], right_[2][2]);
        rotate_clockwise(back_);
    }

    if (rot == "Bi") {
        swap_row_column(upper_, right_, 0, 2);
        swap_row_column(upper_, left_, 0, 0);
        swap_row_column(down_, left_, 2, 0);
        std::swap(upper_[0][0], upper_[0][2]);
        std::swap(down_[2][0], down_[2][2]);
        rotate_counterclockwise(back_);
    }
}

// Swap chosen planes' rows
void Cube::swap_rows(Plane &a, Plane &b, int row_number_a, int row_number_b) {
    for (int i = 0; i < 3; ++i) {
        std::swap(a[row_number_a][i], b[row_number_b][i]);
    }
}

// Swap chosen planes' columns
void Cube::swap_columns(Plane &a, Plane &b, int column_number_a, int column_number_b) {
    for (int i = 0; i < 3; ++i) {
        std::swap(a[i][column_number_a], b[i][column_number_b]);
    }
}

// Swap one plane's row with other's column
void Cube::swap_row_column(Plane &row_plane, Plane &column_plane, int row_number, int column_number) {
    for (int i = 0; i < 3; ++i) {
        std::swap(row_plane[row_number][i], column_plane[i][column_number]);
    }
}

// Rotate plane by 90 degrees clockwise
void Cube::rotate_clockwise(Plane &plane) {
    swap_rows(plane, plane, 0, 2);

    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            std::swap(plane[i][j], plane[j][i]);
        }
    }
}

// Rotate plane by 90 degrees counterclockwise
void Cube::rotate_counterclockwise(Plane &plane) {
    for (int i = 0; i < 3; ++i) {
        rotate_clockwise(plane);
    }
}

// Cube output
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

    std::cout << "Down 5 : \n";
    std::cout << down_;
}

// I HATE N
void Cube::gen_algo_solve(int population_size) {

}

//Getters and setters
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
