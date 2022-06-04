#include "Solver.h"


Solver::Solver() {}

// Layer one solver
void Solver::first_layer(Cube &cube) {

    //STEP 1: CREATE A WHITE CROSS
    // Place the face with white center on the UP
    // Create a 'Daisy' on the UP
    /*   W
     * W Y W
     *   W
     *   */
    if (cube.front_[1][1] == "y")
        cube.rotate_cube("Xi");
    else if (cube.right_[1][1] == "y")
        cube.rotate_cube("Yi");
    else if (cube.left_[1][1] == "y")
        cube.rotate_cube("Y");
    else if (cube.back_[1][1] == "y")
        cube.rotate_cube("X");
    else if (cube.down_[1][1] == "y") {
        cube.rotate_cube("X");
        cube.rotate_cube("X");
    }

    int cross_cells[4][2] = {{0, 1},
                             {1, 0},
                             {1, 2},
                             {2, 1}};

    for (int i = 0; i < 4; ++i) {
        if (cube.left_[cross_cells[i][0]][cross_cells[i][1]] != "w") {
            if (i == 0) {
                cube.rotate("L");
            } else if (i == 1) {
                cube.rotate("L");
                cube.rotate("L");
            } else if (i == 3) {
                cube.rotate("Li");
            }
            move_cell_to_cross(cube, "left", "w");
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (cube.right_[cross_cells[i][0]][cross_cells[i][1]] != "w") {
            if (i == 0) {
                cube.rotate("Ri");
            } else if (i == 1) {
                cube.rotate("Ri");
                cube.rotate("Ri");
            } else if (i == 3) {
                cube.rotate("R");
            }
            move_cell_to_cross(cube, "right", "w");
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (cube.front_[cross_cells[i][0]][cross_cells[i][1]] != "w") {
            if (i == 0) {
                cube.rotate("F");
            } else if (i == 1) {
                cube.rotate("F");
                cube.rotate("F");
            } else if (i == 3) {
                cube.rotate("Fi");
            }
            move_cell_to_cross(cube, "front", "w");
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (cube.back_[cross_cells[i][0]][cross_cells[i][1]] != "w") {
            if (i == 0) {
                cube.rotate("B");
            } else if (i == 1) {
                cube.rotate("B");
                cube.rotate("B");
            } else if (i == 3) {
                cube.rotate("Bi");
            }
            move_cell_to_cross(cube, "back", "w");
        }
    }

}

// find vacant cross cell on the UP plane and replace it
// with chosen color from the plane
/*Plane:
 *  - - -
 *  - - color
 *  - - -
 *  */
void Solver::move_cell_to_cross(Cube &cube, const std::string &plane, const std::string &color) {
    int cross_cells[4][2] = {{2, 1},
                             {1, 2},
                             {0, 1},
                             {1, 0}};

    if (plane == "left") {
        for (int i = 0; i < 4; ++i) {
            if (cube.upper_[cross_cells[i][0]][cross_cells[i][1]] != color) {
                for (int j = 0; j < i; ++j)
                    cube.rotate("U");

                cube.rotate("F");
                break;
            }
        }
    }

    if (plane == "right") {
        cube.rotate_cube("Yi");
        cube.rotate_cube("Yi");
        move_cell_to_cross(cube, "left", color);
    }
    if (plane == "back") {
        cube.rotate_cube("Y");
        move_cell_to_cross(cube, "left", color);
    }
    if (plane == "front") {
        cube.rotate_cube("Zi");
        move_cell_to_cross(cube, "left", color);
    }
}


void Solver::pif_paf() {
    rotate_cube("R");
    rotate_cube("U");
    rotate_cube("Ri");
    rotate_cube("Ui");
}