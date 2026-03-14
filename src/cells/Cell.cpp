#include "cells/Cell.hpp"
#include <SDL3/SDL_log.h>

Cell::~Cell() {}

uint8_t Cell::get_update_frame() const {
    return this->update_each_frame;
}

void Cell::render(Coord pos, uint8_t size, World &world,
                  SDL_Renderer *render) const {
    const SDL_Rect rectangle = { pos.x, pos.y, size, size };
    SDL_SetRenderDrawColor(render,
                           cell_color.r,
                           cell_color.g,
                           cell_color.b,
                           cell_color.a);
    SDL_FRect f_rect;
    SDL_RectToFRect(&rectangle, &f_rect);
    SDL_RenderFillRect(render, &f_rect);
}
