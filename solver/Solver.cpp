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
        cube.rotate_cube("X");
    else if (cube.right_[1][1] == "y")
        cube.rotate_cube("Zi");
    else if (cube.left_[1][1] == "y")
        cube.rotate_cube("Z");
    else if (cube.back_[1][1] == "y")
        cube.rotate_cube("Xi");
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
        }
//        vacant_index = search_vacant_place(cube, "w");
    }

}


void Solver::plane_setup(Cube &cube, const std::string &plane, const std::string &color, const int &cross_index,
                         const int &vacant_index) {
    // Setup to work with a LEFT plane
    if (plane == "right") {
        cube.rotate_cube("Y");
        cube.rotate_cube("Y");
    }
    if (plane == "front") {
        cube.rotate_cube("Y");
    }
    if (plane == "back") {
        cube.rotate_cube("Yi");
    }

    if (cross_index != 1 && vacant_index != -1) {
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
        cube.rotate_cube("L");
        cube.rotate_cube("L");
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
    int vacant_index = search_vacant_place(cube, "w");
    if (vacant_index != -1) {
        for (int j = 0; j < vacant_index; ++j)
            cube.rotate("U");
        cube.rotate("F");
    }
//    if (plane == "left") {
//        for (int i = 0; i < 4; ++i) {
//            if (cube.upper_[cross_cells[i][0]][cross_cells[i][1]] != color) {
//                for (int j = 0; j < i; ++j)
//                    cube.rotate("U");
//
//                cube.rotate("F");
//                break;
//            }
//        }
//    }
//    if (plane == "right") {
//        cube.rotate_cube("Yi");
//        cube.rotate_cube("Yi");
//        move_cell_to_cross(cube, "left", color);
//    }
//    if (plane == "back") {
//        cube.rotate_cube("Y");
//        move_cell_to_cross(cube, "left", color);
//    }
//    if (plane == "front") {
//        cube.rotate_cube("Zi");
//        move_cell_to_cross(cube, "left", color);
//    }
}


void Solver::pif_paf() {
    rotate_cube("R");
    rotate_cube("U");
    rotate_cube("Ri");
    rotate_cube("Ui");
}