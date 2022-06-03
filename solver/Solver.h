#ifndef RUBIKSCUBE_SOLVER_H
#define RUBIKSCUBE_SOLVER_H


#include "../cube/Cube.h"

class Solver: public Cube {
public:
    Cube cube;
public:
    Solver(Cube &cube);

    void first_layer(Cube &cube);

    void pif_paf();
};


#endif //RUBIKSCUBE_SOLVER_H
