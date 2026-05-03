#include "render/Button.hpp"
#include <SDL3/SDL_render.h>

void Button::refresh_canva() {
    const Coord pos = this->get_position();
    const Coord size = this->get_size();
    const float x = static_cast<float>(pos.x);
    const float y = static_cast<float>(pos.y);
    const float sx = static_cast<float>(size.x);
    const float sy = static_cast<float>(size.y);
    button_rect = { x, y, sx, sy };
}

void Button::render() {
    SDL_Renderer* renderer = this->get_renderer();
    SDL_SetRenderDrawColor(renderer, 
                           button_color.r, button_color.g, 
                           button_color.b, button_color.a);
    SDL_RenderFillRect(renderer, &button_rect);
}

void Button::set_color(SDL_Color color) {
    this->button_color = color;
}
