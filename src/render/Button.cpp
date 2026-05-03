#include "render/Button.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>

void Button::refresh_canva() {
    const Coord pos = this->get_position();
    const Coord size = this->get_size();
    const float x = static_cast<float>(pos.x);
    const float y = static_cast<float>(pos.y);
    const float sx = static_cast<float>(size.x);
    const float sy = static_cast<float>(size.y);
    SDL_FRect rect = { x, y, sx, sy };
    button_rect = std::move(rect);
}

void Button::render() {
    SDL_Renderer* renderer = this->get_renderer();
    SDL_SetRenderDrawColor(renderer, 
                           button_color.r, button_color.g, 
                           button_color.b, button_color.a);
    SDL_RenderFillRects(renderer, &button_rect, 1);
}

void Button::set_color(SDL_Color color) {
    this->button_color = color;
}
