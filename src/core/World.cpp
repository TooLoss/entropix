#include "core/World.hpp"
#include <stdexcept>

World::World(Coord size) : size(size), registry() {
    this->grid.assign(size.x * size.y, this->VOID_PIXEL);
}

void World::refresh() {
    for (int i = size.x - 1; i >= 0; i--) {
        for (int j = size.y - 1; j >= 0; j--) {
            Pixel pixel = this->get_pixel(Coord(i,j));
            const Cell& cell = registry.get(pixel.id);
            if (FRAME_BUFFER % cell.get_update_frame() == 0)
                cell.update(Coord(i,j), *this);
        }
    }
}

void World::set_pixel(Coord pos, Pixel pixel) {
    if (is_out_of_range(pos)) {
        throw std::out_of_range("Coordinate set_pixel is out of range.");
    }
    this->grid[pos.vector_to_index(this->size)] = pixel;
}

Pixel World::get_pixel(Coord pos) const {
    if (is_out_of_range(pos)) {
        throw std::out_of_range("Coordinate get_pixel is out of range.");
    }
    return this->grid[pos.vector_to_index(this->size)];
}

bool World::is_empty(Coord pos) {
    if (is_out_of_range(pos)) {
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

Coord World::get_size() const {
    return size;
}

void World::swap(Coord in, Coord out) {
    if (is_out_of_range(in) || is_out_of_range(out)) {
        throw std::out_of_range("Coordinate get_pixel is out of range.");
    }
    Pixel p_in = this->get_pixel(in);
    Pixel p_out = this->get_pixel(out);
    this->set_pixel(out, p_in);
    this->set_pixel(in, p_out);
}

bool World::is_out_of_range(Coord pos) const {
    return (pos.x >= this->size.x || pos.y >= this->size.y || !(pos >= 0));
}

Pixel World::create_pixel_id(CellID id) const {
    return {id};
}
