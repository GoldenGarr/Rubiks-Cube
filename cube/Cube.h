
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
    void print();

    std::string solve();
};


#endif //RUBIKSCUBE_CUBE_H
