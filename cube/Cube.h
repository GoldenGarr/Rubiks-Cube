
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
    Plane lower_;
public:
    Cube();

    Cube(const Plane &front, const Plane &back, const Plane &left, const Plane &right, const Plane &upper,
         const Plane &lower);

    bool validity_check();

    Cube read_file(std::string path);

    Cube generate_random(int random_state = 0);

    void rotate(const std::string &rot);

    void swap_rows(Plane& a, Plane& b, int row_number);

    void gen_algo_solve(int population_size=4000);

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
