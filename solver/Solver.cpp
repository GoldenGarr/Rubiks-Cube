#include "Solver.h"


Solver::Solver(Cube &cube){}

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



}


void Solver::pif_paf() {
    rotate_cube("R");
    rotate_cube("U");
    rotate_cube("Ri");
    rotate_cube("Ui");
}