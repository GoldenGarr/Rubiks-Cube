#ifndef RUBIKSCUBE_GENALGO_H
#define RUBIKSCUBE_GENALGO_H

#include "../cube/Cube.h"

class Genalgo {
public:
    Cube &cube;
    std::vector<std::vector<std::string>> rotations;


    Genalgo(Cube &cube);

    void init(int population_size = 500, int elitism_num = 50,
              int max_generations = 300,
              int max_resets = 10);

    bool fitness_compare(Cube &a, Cube &b);

    int get_fitness(Cube &cube_);

    int get_fitness(Cube &cube_, const std::string &plane);
};


#endif //RUBIKSCUBE_GENALGO_H
