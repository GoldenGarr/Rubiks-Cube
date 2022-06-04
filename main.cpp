#include <iostream>
#include "cube/Cube.h"
#include "solver/Solver.h"

int main() {
//    Cube cube = Cube().read_file("/Users/maksim/CLionProjects/RubiksCube/test_input.txt");
    Cube cube = Cube().generate_random(1000);

    cube.print();

    Solver solver;
//    cube.print();
    std::cout << "----------------\n";
//
    solver.first_layer(cube);
//
    cube.print();

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
