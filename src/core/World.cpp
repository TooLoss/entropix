#include "core/World.hpp"

World::World(Coord size) : size(size) {
    this->grid.assign(size.x * size.y, {0});
}

void World::refresh() {
    for (Coord c : size.all_points()) {
        Pixel current_pixel = grid[c.vector_to_index(size)];
        const std::unique_ptr<Cell> current_cell = registry.get(current_pixel.id);
        current_cell->update(c, *this);
    }
}

void World::set_cell(Coord pos, std::shared_ptr<Cell> new_cell) {
}
