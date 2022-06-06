#ifndef RUBIKSCUBE_SOLVER_H
#define RUBIKSCUBE_SOLVER_H


#include "../cube/Cube.h"
#include <vector>

class Solver : public Cube {
private:
    int cross_cells[4][2] = {{2, 1},
                             {1, 2},
                             {0, 1},
                             {1, 0}};
    int corners_indexes[4][2] = {{2, 2},
                                 {0, 2},
                                 {0, 0},
                                 {2, 0}};
    //    Cube cube;
public:
    Solver();

    void white_cross(Cube &cube);

    void plane_setup(Cube &cube, const std::string &plane, const std::string &color, const int &cross_index,
                     const int &vacant_index);

    int search_vacant_place(Cube &cube, const std::string &color);

    void move_cell_to_cross(Cube &cube, const std::string &plane, const std::string &color);

    void first_layer(Cube &cube);

    int lower_unfinished(Cube &cube);

    void pif_paf(Cube &cube);
};


#endif //RUBIKSCUBE_SOLVER_H
