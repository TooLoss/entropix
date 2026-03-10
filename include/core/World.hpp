#pragma once
#include <vector>
#include <span>
#include <memory>
#include "utils/Coord.hpp"
#include "cells/Cell.hpp"
#include "core/CellRegistry.hpp"

struct Pixel {
    CellID id;
};

class World {
public:
    Pixel VOID_PIXEL = {(CellID)0};

private:
    Coord size;
    std::vector<Pixel> grid;
    CellRegistry registry;

public:
    World(Coord size);

    /** Refresh all pixels in the grid. */
    void refresh();

    /** Set pixel at coordinate pos.
    * @param pos Coord.
    * @param pixel Pixel.
    */
    void set_pixel(Coord pos, Pixel pixel);

    /** Get pixel at coordinate pos.
    * @param pos Coord.
    * @return Pixel value at pos.
    */
    Pixel get_pixel(Coord pos);

    /** Check if the grid is empty at position pos.
    * @param pos Coord.
    * @return true if the grid position is empty.
    */
    bool is_empty(Coord pos);

    /** Get registry reference used to store behavior of cells by id.
    * @return CellRegistry& reference to World Cell Regsitry.
    */
    CellRegistry& get_registry();

    /** Get a reference to the grid.
    * @return std::span<Pixel> grid.
    */
    std::span<Pixel> get_grid();

    /** Get the size of the grid.
    * @return Coord size of the grid.
    */
    Coord get_size();
};
