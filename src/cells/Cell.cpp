#include "cells/Cell.hpp"
#include "core/World.hpp"

void Cell::move_to(Coord in, Coord out, World& world) const {
    Pixel p_in = world.get_pixel(in);
    world.set_pixel(out, p_in);
    world.set_pixel(in, world.VOID_PIXEL);
}
