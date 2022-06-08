#include "Genalgo.h"
#include <random>

Genalgo::Genalgo(Cube &cube) : cube(cube) {
    rotations = {
            {"Fi", "Li", "Bi", "Ri", "Ui", "R",  "Ui", "B",  "L",  "F",  "R",  "U",  "Ri", "U"},
            {"F",  "R",  "B",  "L",  "U",  "Li", "U",  "Bi", "Ri", "Fi", "Li", "Ui", "L",  "Ui"},
            {"U",  "U",  "B",  "U",  "U",  "Bi", "R",  "R",  "F",  "Ri", "Fi", "U",  "U",  "Fi", "U",  "U",  "F", "Ri"},
            {"U",  "U",  "R",  "U",  "U",  "Ri", "F",  "F",  "L",  "Fi", "Li", "U",  "U",  "Li", "U",  "U",  "L", "Fi"},
            {"Ui", "B",  "B",  "D",  "D",  "Li", "F",  "F",  "D",  "D",  "B",  "B",  "Ri", "Ui"},
            {"U",  "B",  "B",  "D",  "D",  "R",  "F",  "F",  "D",  "D",  "B",  "B",  "L",  "U"},
            {"Di", "Ri", "D",  "R",  "R",  "Ui", "R",  "B",  "B",  "L",  "Ui", "Li", "B",  "B",  "U",  "R",  "R"},
            {"D",  "L",  "Di", "L",  "L",  "U",  "Li", "B",  "B",  "Ri", "U",  "R",  "B",  "B",  "Ui", "L",  "L"},
            {"Ri", "U",  "Li", "U",  "U",  "R",  "Ui", "L",  "Ri", "U",  "Li", "U",  "U",  "R",  "Ui", "L",  "Ui"},
            {"L",  "Ui", "R",  "U",  "U",  "Li", "U",  "Ri", "L",  "Ui", "R",  "U",  "U",  "Li", "U",  "Ri", "U"},
            {"Fi", "U",  "B",  "Ui", "F",  "U",  "Bi", "Ui"},
            {"F",  "Ui", "Bi", "U",  "Fi", "Ui", "B",  "U"},
            {"Li", "U",  "U",  "L",  "Ri", "F",  "F",  "R"},
            {"Ri", "U",  "U",  "R",  "Li", "B",  "B",  "L"},
            {"M",  "M",  "U",  "M",  "M",  "U",  "U",  "M",  "M",  "U",  "M",  "M"}
    };
}

void Genalgo::init(int population_size, int elitism_num,
                   int max_generations,
                   int max_resets) {
    std::vector<std::string> initial_shuffle = {};

    for (int j = 0; j < max_resets; ++j) {
        // Randomized population init
        std::vector<Cube> cubes;
        for (int i = 0; i < population_size; ++i) {
            Cube c = cube;
            c.random_single_move(2);
            cubes.push_back(c);
        }

        for (int gen = 0; gen < max_generations; ++gen) {
            // Order cubes by fitness rate
            std::sort(cubes.begin(), cubes.end(), [this](Cube &a, Cube &b) {
                return get_fitness(a) < get_fitness(b);
            });


            // Init randomizer
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> cube_picker(0, elitism_num);
            std::uniform_int_distribution<std::mt19937::result_type> evolution_picker(0, 5);

            if (gen % 20 == 0)
                std::cout << gen << ") "<< get_fitness(cubes[0]) << "\n";

            // Elitism filter + fitness function minimization
            for (int i = 0; i < cubes.size(); ++i) {
                if (get_fitness(cubes[i]) == 0) {
                    std::cout << "Solution found: \n";
                    for (auto &rotation : cubes[i].commands_sequence) {
                        std::cout << rotation;
                    }
                    return;
                }

                // The elitists go without any changes
                if (i > elitism_num) {
                    cubes[i] = cubes[cube_picker(rng)];

                    // Evolution path
                    int evolution_type = evolution_picker(rng);

                    if (evolution_type == 0) {
                        random_permutations(cubes[i]);
                    }
                    if (evolution_type == 1) {
                        random_permutations(cubes[i], 2);
                    }
                    if (evolution_type == 2) {
                        cubes[i].random_rotation();
                        random_permutations(cubes[i]);
                    }
                    if (evolution_type == 3) {
                        cubes[i].random_orientation();
                        random_permutations(cubes[i]);
                    }
                    if (evolution_type == 4) {
                        cubes[i].random_rotation();
                        cubes[i].random_orientation();
                        random_permutations(cubes[i]);
                    }
                    if (evolution_type == 5) {
                        cubes[i].random_orientation();
                        cubes[i].random_rotation();
                        random_permutations(cubes[i]);
                    }
                }
            }

        }
//        for (auto & cube : cubes) {
//            std::cout << get_fitness(cube) << " ";
//        }
    }
    std::cout << "GG\n";
}

void Genalgo::random_permutations(Cube &cube_, int n) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> cube_picker(0, 14);

    for (int i = 0; i < n; ++i) {
        cube_.rotate(rotations[cube_picker(dev)]);
    }

}

int Genalgo::get_fitness(Cube &cube_) {
    int counter = get_fitness(cube_, "front") + get_fitness(cube_, "back")
                  + get_fitness(cube_, "left") + get_fitness(cube_, "right")
                  + get_fitness(cube_, "upper") + get_fitness(cube_, "down");
    return counter;
}

int Genalgo::get_fitness(Cube &cube_, const std::string &plane) {
    int counter = 0;
    if (plane == "front") {
        std::string center = cube_.front_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube_.front_[i][j] != center);
            }
        }
    }

    if (plane == "left") {
        std::string center = cube_.left_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube_.left_[i][j] != center);
            }
        }
    }

    if (plane == "right") {
        std::string center = cube_.right_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube_.right_[i][j] != center);
            }
        }
    }

    if (plane == "back") {
        std::string center = cube_.back_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube_.back_[i][j] != center);
            }
        }
    }

    if (plane == "upper") {
        std::string center = cube_.upper_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube_.upper_[i][j] != center);
            }
        }
    }

    if (plane == "down") {
        std::string center = cube_.down_[1][1];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                counter += (cube_.down_[i][j] != center);
            }
        }
    }
    return counter;
}


