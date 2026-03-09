#pragma once
#include <vector>
#include "cells/Cell.hpp"
#include "utils/Coord.hpp"

class World {
private:
    int y;
    int x;
    std::vector<Cell> grid;

public:
    World(int x, int y);

    void refresh();
    void set_cell(Coord pos, Cell new_cell);
    Cell get_cell(Coord pos) const;
};
