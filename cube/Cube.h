
#ifndef RUBIKSCUBE_CUBE_H
#define RUBIKSCUBE_CUBE_H

#include <iostream>
#include "Plane.h"
#include <string>

class Cube {
private:
    Plane front_;
    Plane back_;
    Plane left_;
    Plane right_;
    Plane upper_;
    Plane down_;
public:
    Cube();

    Cube(Plane front, Plane back, Plane left, Plane right, Plane upper,
         Plane lower);

    bool validity_check();

    Cube read_file(const char *path);

    void to_txt(const std::string& name);

    void assign_cells(Plane &plane, std::ifstream &is);

    Cube generate_random(int n_complexity=20);

    void rotate(const std::string &rot);

    void swap_rows(Plane &a, Plane &b, int row_number_a, int row_number_b);

    void swap_columns(Plane &a, Plane &b, int column_number_a, int column_number_b);

    void swap_row_column(Plane& row_plane, Plane& column_plane, int row_number, int column_number);

    void rotate_clockwise(Plane &plane);

    void rotate_counterclockwise(Plane &plane);

    void gen_algo_solve(int population_size = 4000);

    void print();

    std::string solve();

    const Plane &getFront() const;

    void setFront(const Plane &front);

    const Plane &getBack() const;

    void setBack(const Plane &back);

    const Plane &getLeft() const;

    void setLeft(const Plane &left);

    const Plane &getRight() const;

    void setRight(const Plane &right);

    const Plane &getUpper() const;

    void setUpper(const Plane &upper);

    const Plane &getLower() const;

    void setLower(const Plane &lower);
};


#endif //RUBIKSCUBE_CUBE_H
