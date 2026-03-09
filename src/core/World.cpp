#include "core/World.hpp"
#include "cells/CellVoid.hpp"

World::World(Coord size) : size(size) {
    this->void_cell = std::make_shared<CellVoid>();
    this->grid.assign(size.x * size.y, void_cell);
}

void World::refresh() {
    for (Coord c : this->size.all_points()) {
        const int index = c.vector_to_index(this->size);
        Coord new_pos = grid[index]->update(c);
    }
}

void World::set_cell(Coord pos, std::shared_ptr<Cell> new_cell) {
    grid[pos.vector_to_index(this->size)] = std::move(new_cell);
}
