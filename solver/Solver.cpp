#include "Solver.h"


Solver::Solver() = default;

// White cross solver
void Solver::white_cross(Cube &cube) {

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
        cube.rotate_cube("Zi");
    else if (cube.left_[1][1] == "y")
        cube.rotate_cube("Z");
    else if (cube.back_[1][1] == "y")
        cube.rotate_cube("X");
    else if (cube.down_[1][1] == "y") {
        cube.rotate_cube("X");
        cube.rotate_cube("X");
    }


//    int cross_cells[4][2] = {{2, 1},
//                             {1, 2},
//                             {0, 1},
//                             {1, 0}};

    int vacant_index = search_vacant_place(cube, "w");

    // Until we make a daisy at UP
    while (vacant_index != -1) {
        for (int i = 0; i < 4; ++i) {
            if (cube.left_[cross_cells[i][0]][cross_cells[i][1]] == "w") {
                plane_setup(cube, "left", "w", i, vacant_index);
                vacant_index = search_vacant_place(cube, "w");
            }

            if (cube.right_[cross_cells[i][0]][cross_cells[i][1]] == "w") {
                plane_setup(cube, "right", "w", i, vacant_index);
                vacant_index = search_vacant_place(cube, "w");
            }

            if (cube.back_[cross_cells[i][0]][cross_cells[i][1]] == "w") {
                plane_setup(cube, "back", "w", i, vacant_index);
                vacant_index = search_vacant_place(cube, "w");
            }

            if (cube.front_[cross_cells[i][0]][cross_cells[i][1]] == "w") {
                plane_setup(cube, "front", "w", i, vacant_index);
                vacant_index = search_vacant_place(cube, "w");
            }

            if (cube.down_[cross_cells[i][0]][cross_cells[i][1]] == "w") {
                if (vacant_index != -1 && i != 2) {
                    /* Transform the down plane to:
                     *  - w -
                     *  - - -
                     *  - - -
                     */
                    if (i == 0) {
                        cube.rotate("Di");
                        cube.rotate("Di");
                    } else if (i == 1) {
                        cube.rotate("Di");
                    } else {
                        cube.rotate("D");
                    }
                }

                for (int j = 0; j < vacant_index; ++j) {
                    cube.rotate("U");
                }

                cube.rotate("F");
                cube.rotate("F");
                vacant_index = search_vacant_place(cube, "w");
            }
        }
    }
    // 'Daisy' on UP completed

    // Move the white cross to the DOWN (with edge color respectively)
    while (cube.front_[0][1] != cube.front_[1][1]) {
        cube.rotate("U");
    }
    cube.rotate("F");
    cube.rotate("F");
//
    while (cube.left_[0][1] != cube.left_[1][1]) {
        cube.rotate("U");
    }
    cube.rotate("L");
    cube.rotate("L");
//
    while (cube.right_[0][1] != cube.right_[1][1]) {
        cube.rotate("U");
    }
    cube.rotate("R");
    cube.rotate("R");
//
    while (cube.back_[0][1] != cube.back_[1][1]) {
        cube.rotate("U");
    }
    cube.rotate("B");
    cube.rotate("B");
}


// Utility to form a DAISY
void Solver::plane_setup(Cube &cube, const std::string &plane, const std::string &color, const int &cross_index,
                         const int &vacant_index) {
    // Setup to work with a LEFT plane
    if (plane == "right") {
        cube.rotate_cube("Yi");
        cube.rotate_cube("Yi");
    }
    if (plane == "front") {
        cube.rotate_cube("Yi");
    }
    if (plane == "back") {
        cube.rotate_cube("Y");
    }

    if (vacant_index != -1) {
        for (int j = 0; j <= vacant_index; ++j) {
            cube.rotate("U");
        }
    }

    // Get plane
    /* - - -
    *  - - color
    *  - - -
    */
    if (cross_index == 0) {
        cube.rotate("Li");
    } else if (cross_index == 2) {
        cube.rotate("L");
    } else if (cross_index == 3) {
        cube.rotate("L");
        cube.rotate("L");
    }
    move_cell_to_cross(cube, "left", "w");
}


// Search for vacant place on upper
int Solver::search_vacant_place(Cube &cube, const std::string &color) {
    for (int i = 0; i < 4; ++i) {
        if (cube.upper_[cross_cells[i][0]][cross_cells[i][1]] != color)
            return i;
    }
    return -1;
}

// Replace the vacant cross place with chosen color from the plane
/*Plane:
 *  - - -
 *  - - color
 *  - - -
 *  */
void Solver::move_cell_to_cross(Cube &cube, const std::string &plane, const std::string &color) {
    int vacant_index = search_vacant_place(cube, color);
    for (int j = 0; j < vacant_index; ++j)
        cube.rotate("U");
    cube.rotate("F");
}


// Solve the white plane + lower layer
void Solver::first_layer(Cube &cube) {
    while (lower_unfinished(cube) > 0) {
        for (int i = 0; i < 4; ++i) {
            if (cube.left_[corners_indexes[i][0]][corners_indexes[i][1]] == "w") {

                /*
                 *      - - -
                 *      - - -
                 *      - - X
                 * */
                if (i == 0) {
                    std::string color_1 = cube.down_[0][0];
                    std::string color_2 = cube.front_[2][0];

                    while (!((cube.front_[1][1] == color_2 && cube.left_[1][1] == color_1)
                             || (cube.front_[1][1] == color_1 && cube.left_[1][1] == color_2))) {
                        cube.rotate_cube("Y");
                        cube.rotate("Di");
                    }

                    cube.rotate("Y");
                    while (cube.down_[0][2] != "w")
                        pif_paf(cube);
                }

                /*
                 *      - - X
                 *      - - -
                 *      - - -
                 * */
                if (i == 1) {
                    std::string color_1 = cube.front_[0][0];
                    std::string color_2 = cube.upper_[2][0];

                    while (!((cube.front_[1][1] == color_2 && cube.left_[1][1] == color_1)
                             || (cube.front_[1][1] == color_1 && cube.left_[1][1] == color_2))) {
                        cube.rotate_cube("Y");
                        cube.rotate("U");
                    }

                    cube.rotate("Y");
                    while (cube.down_[0][2] != "w")
                        pif_paf(cube);
                }

                /*
                 *      X - -
                 *      - - -
                 *      - - -
                 * */
                if (i == 2) {
                    std::string color_1 = cube.upper_[0][0];
                    std::string color_2 = cube.back_[0][2];

                    while (!((cube.back_[1][1] == color_2 && cube.left_[1][1] == color_1)
                             || (cube.back_[1][1] == color_1 && cube.left_[1][1] == color_2))) {
                        cube.rotate_cube("Y");
                        cube.rotate("U");
                    }

                    cube.rotate("Y");
                    cube.rotate("Y");
                    while (cube.down_[0][2] != "w")
                        pif_paf(cube);
                }

                /*
                 *      - - -
                 *      - - -
                 *      X - -
                 * */
                if (i == 3) {
                    std::string color_1 = cube.back_[2][2];
                    std::string color_2 = cube.down_[2][0];

                    while (!((cube.back_[1][1] == color_2 && cube.left_[1][1] == color_1)
                             || (cube.back_[1][1] == color_1 && cube.left_[1][1] == color_2))) {
                        cube.rotate_cube("Y");
                        cube.rotate("Di");
                    }

                    cube.rotate("Y");
                    cube.rotate("Y");
                    while (cube.down_[0][0] != "w")
                        pif_paf(cube);
                }
            }
        }
        cube.rotate("Y");

        for (int i = 0; i < 4; ++i) {
            if (cube.upper_[corners_indexes[i][0]][corners_indexes[i][1]] == "w") {
                if (i == 0) {
                    std::string color_1 = cube.right_[0][0];
                    std::string color_2 = cube.front_[0][2];

                    while (!((cube.right_[1][1] == color_2 && cube.front_[1][1] == color_1)
                             || (cube.right_[1][1] == color_1 && cube.front_[1][1] == color_2))) {
                        cube.rotate_cube("Y");
                        cube.rotate("U");
                    }
                    while (cube.down_[0][0] != "w")
                        pif_paf(cube);
                }

                if (i == 1) {
                    std::string color_1 = cube.right_[0][2];
                    std::string color_2 = cube.back_[0][0];


                    while (!((cube.right_[1][1] == color_2 && cube.back_[1][1] == color_1)
                             || (cube.right_[1][1] == color_1 && cube.back_[1][1] == color_2))) {
                        cube.rotate_cube("Y");
                        cube.rotate("U");
                    }

                    cube.rotate_cube("Yi");
                    while (cube.down_[0][0] != "w")
                        pif_paf(cube);
                }

                if (i == 2) {
                    std::string color_1 = cube.back_[0][2];
                    std::string color_2 = cube.left_[0][0];


                    while (!((cube.left_[1][1] == color_2 && cube.back_[1][1] == color_1)
                             || (cube.left_[1][1] == color_1 && cube.back_[1][1] == color_2))) {
                        cube.rotate_cube("Y");
                        cube.rotate("U");
                    }

                    cube.rotate_cube("Yi");
                    cube.rotate_cube("Yi");
                    while (cube.down_[0][0] != "w")
                        pif_paf(cube);
                }

                if (i == 3) {
                    std::string color_1 = cube.left_[0][2];
                    std::string color_2 = cube.front_[0][0];


                    while (!((cube.left_[1][1] == color_2 && cube.front_[1][1] == color_1)
                             || (cube.left_[1][1] == color_1 && cube.front_[1][1] == color_2))) {
                        cube.rotate_cube("Y");
                        cube.rotate("U");
                    }

                    cube.rotate_cube("Y");
                    while (cube.down_[0][0] != "w")
                        pif_paf(cube);
                }
            }
        }


    }
}

// Find corners of chosen color
//void Solver::search_corners(Cube &cube, const std::string &color) {
//
//}

// Is the DOWN plaene unfinished
int Solver::lower_unfinished(Cube &cube) {
    int cells_left = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (cube.down_[i][j] != "w")
                ++cells_left;
        }
    }
    return cells_left;
}


void Solver::pif_paf(Cube &cube) {
    cube.rotate_cube("R");
    cube.rotate_cube("U");
    cube.rotate_cube("Ri");
    cube.rotate_cube("Ui");
}