#ifndef RUBIKSCUBE_PLANE_H
#define RUBIKSCUBE_PLANE_H

#include <iostream>
#include "Cell.h"


class Plane {
private:
    std::string cells_[3][3];
public:
    Plane(std::string color);

    Plane();

    friend std::ostream& operator<<(std::ostream& os, const Plane& plane);

    std::string *operator[](int index);
};


#endif //RUBIKSCUBE_PLANE_H
