#include "render/Canva.hpp"

Coord Canva::get_position() const {
    return pos;
}

Coord Canva::get_size() const {
    return size;
}

Coord Canva::get_canvas_location(Coord relative_pos) const {
    return pos + relative_pos;
}

void Canva::set_size(const Coord size) {
    this->size = size;
}
