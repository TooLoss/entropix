#pragma once
#include <cstdint>
#include <SDL3/SDL_render.h>
#include "utils/Coord.hpp"

class World;

enum class Mobility : uint8_t {
    STATIC,     // Will not move no matter what
    MOVABLE,    // Will not move except if pushed
    DYNAMIC     // Will move each frame
};

enum class State : uint8_t {
    SOLID,
    LIQUID
};

class Cell {
private:
    Mobility mobility = Mobility::STATIC;
    State state = State::SOLID;
    uint8_t update_each_frame = 1;

protected:
    SDL_Color cell_color = { 255, 255, 255, 255 };

public:
    Cell(SDL_Color color) : cell_color(color) {}

    virtual ~Cell();

    virtual void update(Coord &pos, World &world) const = 0;

    virtual void render(Coord &pos, World &world, SDL_Renderer *renderer, const SDL_FRect *rect) const;

    State get_state() const;

    uint8_t get_update_frame() const;
};
