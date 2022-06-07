#include <iostream>
#include "cube/Cube.h"
#include "solver/Solver.h"
#include "solver/Genalgo.h"


int main() {
//    Cube cube = Cube().read_file("/Users/maksim/CLionProjects/RubiksCube/test_input.txt");
    Cube cube = Cube().generate_random(100);
    Genalgo g = Genalgo(cube);
    g.cube.print();

    std::cout << "----------------\n";

//    g.cube.rotate(g.rotations[1]);
    g.cube.random_rotation(10);
    g.cube.print();

//    std::cout << g.get_fitness();

//    Solver solver;
//    solver.white_cross(cube);
//
//    cube.print();
//
//    solver.first_layer(cube);
//    cube.print();




//    std::string rot;
//    while (rot != "E") {
//        std::cout << "Enter the direction:";
//        std::cin >> rot;
////        cube.rotate(rot);
//        cube.rotate_cube(rot);
//        cube.print();
//    }

//    cube.to_txt("ajsdjkadjs");

    return 0;
}
