#include "render/TerminalRender.hpp"
#include <iomanip>
#include <iostream>

TerminalRender::TerminalRender(World& world) : world(world) {}

void TerminalRender::print() const {
    Coord size = world.get_size();
    for (int j = 0; j < size.y; j++) {
        for (int i = 0; i < size.x; i++) {
            Coord coord = Coord(i,j);
            CellID id = world.get_pixel(coord).id;
            std::cout << std::setw(3) << unsigned(static_cast<uint8_t>(id)) << " ";
        }
        std::cout << std::endl;
    }
}

