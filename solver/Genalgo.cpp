#include "Genalgo.h"

Genalgo::Genalgo(Cube &cube) : cube(cube) {
    rotations = {
                        {"Fi", "Li", "Bi", "Ri", "Ui", "R", "Ui", "B", "L", "F", "R", "U", "Ri", "U"},
                        {"F", "R", "B", "L", "U", "Li", "U", "Bi", "Ri", "Fi", "Li", "Ui", "L", "Ui"},
                        {"U", "U", "B", "U", "U", "Bi", "R", "R", "F", "Ri", "Fi", "U", "U", "Fi", "U", "U", "F", "Ri"},
                        {"U", "U", "R", "U", "U", "Ri", "F", "F", "L", "Fi", "Li", "U", "U", "Li", "U", "U", "L", "Fi"},
                        {"Ui", "B", "B", "D", "D", "Li", "F", "F", "D", "D", "B", "B", "Ri", "Ui"},
                        {"U", "B", "B", "D", "D", "R", "F", "F", "D", "D", "B", "B", "L", "U"},
                        {"Di", "Ri", "D", "R", "R", "Ui", "R", "B", "B", "L", "Ui", "Li", "B", "B", "U", "R", "R"},
                        {"D", "L", "Di", "L", "L", "U", "Li", "B", "B", "Ri", "U", "R", "B", "B", "Ui", "L", "L"},
                        {"Ri", "U", "Li", "U", "U", "R", "Ui", "L", "Ri", "U", "Li", "U", "U", "R", "Ui", "L", "Ui"},
                        {"L", "Ui", "R", "U", "U", "Li", "U", "Ri", "L", "Ui", "R", "U", "U", "Li", "U", "Ri", "U"},
                        {"Fi", "U", "B", "Ui", "F", "U", "Bi", "Ui"},
                        {"F", "Ui", "Bi", "U", "Fi", "Ui", "B", "U"},
                        {"Li", "U", "U", "L", "Ri", "F", "F", "R"},
                        {"Ri", "U", "U", "R", "Li", "B", "B", "L"},
                        {"M", "M", "U", "M", "M", "U", "U", "M", "M", "U", "M", "M"}
    };
}

void Genalgo::init(int population_size) {
    std::vector<std::string> initial_shuffle = {};

    std::vector<Cube> cubes;
    for (int i = 0; i < population_size; ++i) {
        Cube c(cube);
        c.rotate(initial_shuffle);
        c.random_rotation();
//        cube.
    }
}


int Genalgo::get_fitness() {
    int counter = get_fitness("front") + get_fitness("back") + get_fitness("left")
            + get_fitness("right") + get_fitness("upper") + get_fitness("down");
    return counter;
}

int Genalgo::get_fitness(const std::string &plane) {
    int counter = 0;
    if (plane == "front") {
        std::string center = cube.front_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube.front_[i][j] != center);
            }
        }
    }

    if (plane == "left") {
        std::string center = cube.left_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube.left_[i][j] != center);
            }
        }
    }

    if (plane == "right") {
        std::string center = cube.right_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube.right_[i][j] != center);
            }
        }
    }

    if (plane == "back") {
        std::string center = cube.back_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube.back_[i][j] != center);
            }
        }
    }

    if (plane == "upper") {
        std::string center = cube.upper_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube.upper_[i][j] != center);
            }
        }
    }

    if (plane == "down") {
        std::string center = cube.down_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube.down_[i][j] != center);
            }
        }
    }
    return counter;
}


