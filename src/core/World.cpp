#include "core/World.hpp"
#include <stdexcept>

World::World(Coord size) : size(size) {
    this->grid.assign(size.x * size.y, this->VOID_PIXEL);
}

void World::refresh() {
    for (Coord c : size.all_points()) {
        Pixel current_pixel = grid[c.vector_to_index(size)];
        const Cell& current_cell = registry.get(current_pixel.id);
        current_cell.update(c, *this);
    }
}

void World::set_pixel(Coord pos, Pixel pixel) {
    if (pos.x > this->size.x || pos.y > this->size.y) {
        throw std::out_of_range("Coordinate set_pixel is out of range.");
    }
    this->grid[pos.vector_to_index(this->size)] = pixel;
}

Pixel World::get_pixel(Coord pos) {
    if (pos.x > this->size.x || pos.y > this->size.y) {
        throw std::out_of_range("Coordinate get_pixel is out of range.");
    }
    return this->grid[pos.vector_to_index(this->size)];
}

bool World::is_empty(Coord pos) {
    if (pos.x >= this->size.x || pos.y >= this->size.y) {
        return false;
    }
    Pixel pixel = this->get_pixel(pos);
    return pixel.id == CellID::VOID;
}

CellRegistry& World::get_registry() {
    return registry;
}

std::span<Pixel> World::get_grid() {
    return grid;
}

Coord World::get_size() {
    return size;
}
