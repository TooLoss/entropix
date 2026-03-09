#pragma once
#include <vector>
#include <memory>
#include "utils/Coord.hpp"
#include "cells/Cell.hpp"
#include "core/CellRegistry.hpp"

struct Pixel {
    int id;
};

class World {
private:
    Coord size;
    std::vector<Pixel> grid;
    CellRegistry registry;

public:
    World(Coord size);

    void init_cells();
    void refresh();
    void set_pixel(Coord pos, Pixel pixel);
    Pixel get_pixel(Coord pos);
    bool is_empty(Coord pos);
    CellRegistry& get_registry();
    std::vector<Pixel>& get_grid();
    Coord get_size();
};
