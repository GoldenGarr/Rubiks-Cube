#ifndef RUBIKSCUBE_SOLVER_H
#define RUBIKSCUBE_SOLVER_H


#include "../cube/Cube.h"

class Solver: public Cube {
public:
//    Cube cube;
public:
    Solver();

    void first_layer(Cube &cube);

    void move_cell_to_cross(Cube &cube, const std::string& plane, const std::string& color);

    void pif_paf();
};


#endif //RUBIKSCUBE_SOLVER_H
