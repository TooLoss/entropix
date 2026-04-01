#pragma once
#include "utils/Coord.hpp"

class Canva {
private:
    Coord pos;
    Coord size;

public:
    Canva(Coord pos, Coord size) : pos(pos), size(size) {}

    Coord get_position() const;
    Coord get_size() const;
    Coord get_canvas_location(Coord relative_pos) const;

    void set_size(const Coord size);
};
