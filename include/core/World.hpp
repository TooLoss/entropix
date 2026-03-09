#pragma once
#include <vector>
#include <memory>
#include "cells/Cell.hpp"
#include "utils/Coord.hpp"

class World {
private:
    Coord size;
    std::vector<std::shared_ptr<Cell>> grid;
    std::shared_ptr<Cell> void_cell;

public:
    World(Coord size);

    void refresh();
    void set_cell(Coord pos, std::shared_ptr<Cell> new_cell);
    std::shared_ptr<Cell> get_cell(Coord pos) const;
};
