#include "cells/Cell.hpp"
#include <SDL3/SDL_log.h>

Cell::~Cell() {}

uint8_t Cell::get_update_frame() const {
    return this->update_each_frame;
}

void Cell::render(Coord pos, World &world, SDL_Renderer *renderer, const SDL_FRect *rect) const {
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer,
                           cell_color.r,
                           cell_color.g,
                           cell_color.b,
                           cell_color.a);
    SDL_RenderFillRect(renderer, rect);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
