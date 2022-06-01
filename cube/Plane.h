#ifndef RUBIKSCUBE_PLANE_H
#define RUBIKSCUBE_PLANE_H

#include <iostream>
#include "Cell.h"


class Plane {
private:
    int cells_[3][3];
public:
    Plane(int color);

    Plane();

    friend std::ostream& operator<<(std::ostream& os, const Plane& plane);

    int *operator[](int index);
};


#endif //RUBIKSCUBE_PLANE_H
