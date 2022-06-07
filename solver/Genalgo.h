#ifndef RUBIKSCUBE_GENALGO_H
#define RUBIKSCUBE_GENALGO_H

#include "../cube/Cube.h"

class Genalgo {
public:
    Cube &cube;
    std::vector<std::vector<std::string>> rotations;

    Genalgo(Cube &cube);

    void init(int population_size=500);

    int get_fitness();

    int get_fitness(const std::string &plane);
};


#endif //RUBIKSCUBE_GENALGO_H
