#pragma once
#include <SDL3/SDL_render.h>
#include "core/World.hpp"

class SdlGridRenderer {
private:
    World& world;
    SDL_Renderer* renderer;
    SDL_Window* window;
    uint8_t cell_size{1};

    std::vector<SDL_FRect> render_grid;

public:
    SdlGridRenderer(World& world, SDL_Renderer* renderer, SDL_Window* window);

    void refresh_window() const;

    void calculate_size();

    void create_render_grid();
};
