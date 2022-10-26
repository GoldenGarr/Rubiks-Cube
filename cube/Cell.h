#ifndef RUBIKSCUBE_CELL_H
#define RUBIKSCUBE_CELL_H


class Cell {
private:
    // 0: Red, 1: Orange, 2: Yellow, 3: White, 4: Green, 5: Blue
    int color_;
public:
    Cell();

    Cell(int color);

    int getColor() const;

    void setColor(int color);
};


#endif //RUBIKSCUBE_CELL_H
