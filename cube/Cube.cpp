#include "Cube.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <utility>
#include <random>


Cube& Cube::operator=(const Cube& other) {
    if (this != &other) {
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->left_ = other.left_;
        this->right_ = other.right_;
        this->down_ = other.down_;
        this->upper_ = other.upper_;
    }

    return *this;
}

//Cube::Cube(Cube &other) {
//    // TODO: check if == this
//    this->front_ = Plane();
//    this->back_ = Plane();
//    this->left_ = Plane();
//    this->right_ = Plane();
//    this->upper_ = Plane();
//    this->down_ = Plane();
//
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            this->front_[i][j] = other.front_[i][j];
//            this->back_[i][j] = other.back_[i][j];
//            this->left_[i][j] = other.left_[i][j];
//            this->right_[i][j] = other.right_[i][j];
//            this->upper_[i][j] = other.upper_[i][j];
//            this->down_[i][j] = other.down_[i][j];
//        }
//    }
//}


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
    Cube cube;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,11); // distribution in range [1, 6]

    for (int i = 0; i < n_complexity; ++i)
        cube.rotate(rotations[dist(rng)]);

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
        commands_sequence.emplace_back("U");
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
        commands_sequence.emplace_back("Ui");
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
        commands_sequence.emplace_back("D");
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
        commands_sequence.emplace_back("Di");
    }

    if (rot == "R") {
        swap_columns(front_, upper_, 2, 2);
        swap_columns(front_, back_, 2, 0);
        swap_columns(front_, down_, 2, 2);
        std::swap(back_[0][0], back_[2][0]);
        std::swap(down_[0][2], down_[2][2]);
        rotate_clockwise(right_);
        commands_sequence.emplace_back("R");
    }

    if (rot == "Ri") {
        swap_columns(front_, down_, 2, 2);
        swap_columns(front_, back_, 2, 0);
        swap_columns(front_, upper_, 2, 2);
        std::swap(back_[0][0], back_[2][0]);
        std::swap(upper_[0][2], upper_[2][2]);
        rotate_counterclockwise(right_);
        commands_sequence.emplace_back("Ri");
    }

    if (rot == "L") {
        swap_columns(front_, down_, 0, 0);
        swap_columns(front_, back_, 0, 2);
        swap_columns(front_, upper_, 0, 0);
        std::swap(back_[0][2], back_[2][2]);
        std::swap(upper_[0][0], upper_[2][0]);
        rotate_clockwise(left_);
        commands_sequence.emplace_back("L");
    }

    if (rot == "Li") {
        swap_columns(front_, upper_, 0, 0);
        swap_columns(front_, back_, 0, 2);
        swap_columns(front_, down_, 0, 0);
        std::swap(back_[0][2], back_[2][2]);
        std::swap(down_[0][0], down_[2][0]);
        rotate_counterclockwise(left_);
        commands_sequence.emplace_back("Li");
    }

    if (rot == "F") {
        swap_row_column(upper_, right_, 2, 0);
        swap_row_column(upper_, left_, 2, 2);
        swap_row_column(down_, left_, 0, 2);
        std::swap(upper_[2][0], upper_[2][2]);
        std::swap(down_[0][0], down_[0][2]);
        rotate_clockwise(front_);
        commands_sequence.emplace_back("F");
    }

    if (rot == "Fi") {
        swap_row_column(down_, left_, 0, 2);
        swap_row_column(upper_, left_, 2, 2);
        swap_row_column(upper_, right_, 2, 0);
        std::swap(left_[0][2], left_[2][2]);
        std::swap(right_[0][0], right_[2][0]);
        rotate_counterclockwise(front_);
        commands_sequence.emplace_back("Fi");
    }

    if (rot == "B") {
        swap_row_column(down_, left_, 2, 0);
        swap_row_column(upper_, left_, 0, 0);
        swap_row_column(upper_, right_, 0, 2);
        std::swap(left_[0][0], left_[2][0]);
        std::swap(right_[0][2], right_[2][2]);
        rotate_clockwise(back_);
        commands_sequence.emplace_back("B");
    }

    if (rot == "Bi") {
        swap_row_column(upper_, right_, 0, 2);
        swap_row_column(upper_, left_, 0, 0);
        swap_row_column(down_, left_, 2, 0);
        std::swap(upper_[0][0], upper_[0][2]);
        std::swap(down_[2][0], down_[2][2]);
        rotate_counterclockwise(back_);
        commands_sequence.emplace_back("Bi");
    }

    if (rot == "M") {
        rotate_cube("X");
        rotate("R");
        rotate("Li");
    }

    if (rot == "L2") {
        rotate("L");
        rotate("L");
    }

    if (rot == "F2") {
        rotate("F");
        rotate("F");
    }

    if (rot == "R2") {
        rotate("R");
        rotate("R");
    }

    if (rot == "U2") {
        rotate("U");
        rotate("U");
    }

    if (rot == "B2") {
        rotate("B");
        rotate("B");
    }

    if (rot == "D2") {
        rotate("D");
        rotate("D");
    }
}

void Cube::rotate(const std::vector<std::string> &rotations) {
    for (auto &rot: rotations)
        rotate(rot);
}

void Cube::random_single_move(int n) {
    std::string rotations[18] = {"U", "Ui", "D", "Di", "R", "Ri",
                                 "L", "Li", "F", "Fi", "B", "Bi", "L2", "R2", "F2", "B2", "U2", "D2"};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,17);

    for (int i = 0; i < n; ++i)
        rotate(rotations[dist(rng)]);
}

void Cube::random_rotation(int n) {
    std::string rotations[6] = {"X", "Xi", "X2", "Y", "Yi", "Y2"};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,5);

    for (int i = 0; i < n; ++i)
        rotate_cube(rotations[dist(rng)]);
}

void Cube::random_orientation(int n) {
    std::string rotations[6] = {"Z", "Zi", "Z2"};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,2);

    for (int i = 0; i < n; ++i)
        rotate_cube(rotations[dist(rng)]);
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

void Cube::swap_planes(Plane &a, Plane &b) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::swap(a[i][j], b[i][j]);
        }
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

void Cube::rotate_cube(const std::string &rot) {
    if (rot == "Y") {
        // Rotate the entire cube by Y axis: LEFT plane -> FRONT plane
        swap_planes(front_, right_);
        swap_planes(front_, back_);
        swap_planes(front_, left_);

        rotate_counterclockwise(upper_);
        rotate_clockwise(down_);

        commands_sequence.emplace_back("_Y_");
    }
    if (rot == "Yi") {
        // Rotate the entire cube by Y axis: RIGHT plane -> FRONT plane
        swap_planes(front_, left_);
        swap_planes(front_, back_);
        swap_planes(front_, right_);

        rotate_clockwise(upper_);
        rotate_counterclockwise(down_);
        commands_sequence.emplace_back("_Yi_");
    }
    if (rot == "X") {
        // Rotate the entire cube by X axis: UP plane -> FRONT plane
        swap_planes(front_, down_);
        swap_planes(front_, back_);
        swap_planes(front_, upper_);

        rotate_clockwise(upper_);
        rotate_clockwise(upper_);

        rotate_clockwise(back_);
        rotate_clockwise(back_);

        rotate_counterclockwise(right_);
        rotate_clockwise(left_);

        commands_sequence.emplace_back("_X_");
    }
    if (rot == "Xi") {
        // Rotate the entire cube by X axis: DOWN plane -> FRONT plane
        swap_planes(front_, upper_);
        swap_planes(front_, back_);
        swap_planes(front_, down_);

        rotate_clockwise(down_);
        rotate_clockwise(down_);

        rotate_clockwise(back_);
        rotate_clockwise(back_);

        rotate_clockwise(right_);
        rotate_counterclockwise(left_);
        commands_sequence.emplace_back("_Xi_");
    }
    if (rot == "Z") {
        // Rotate the entire cube by Z axis: LEFT plane -> UP plane

        swap_planes(upper_, right_);
        swap_planes(upper_, down_);
        swap_planes(upper_, left_);

        rotate_clockwise(upper_);
        rotate_clockwise(right_);
        rotate_clockwise(left_);
        rotate_clockwise(down_);

        rotate_clockwise(front_);
        rotate_counterclockwise(back_);

        commands_sequence.emplace_back("_Z_");
    }
    if (rot == "Zi") {
        // Rotate the entire cube by Zi axis: RIGHT plane -> UP plane

        swap_planes(upper_, left_);
        swap_planes(upper_, down_);
        swap_planes(upper_, right_);

        rotate_counterclockwise(upper_);
        rotate_counterclockwise(right_);
        rotate_counterclockwise(left_);
        rotate_counterclockwise(down_);

        rotate_counterclockwise(front_);
        rotate_clockwise(back_);
        commands_sequence.emplace_back("_Zi_");
    }

    if (rot == "X2") {
        rotate_cube("X");
        rotate_cube("X");
    }

    if (rot == "Y2") {
        rotate_cube("Y");
        rotate_cube("Y");
    }

    if (rot == "Z2") {
        rotate_cube("Z");
        rotate_cube("Z");
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


