#include <algorithm>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_log.h>
#include "render/SdlGridRenderer.hpp"

SdlGridRenderer::SdlGridRenderer(World &world, SDL_Renderer *renderer, SDL_Window* window)
    : world(world), renderer(renderer), window(window) {
    calculate_size();
}

void SdlGridRenderer::refresh_window() const {
    Coord size = this->world.get_size();
    for (int i = size.x - 1; i >= 0; i--) {
        for (int j = size.y - 1; j >= 0; j--) {
            Pixel pixel = world.get_pixel(Coord(i,j));
            const Cell& cell = world.get_registry().get(pixel.id);
            Coord world_pos(i*cell_size, j*cell_size);
            cell.render(world_pos, cell_size, world, renderer);
        }
    }
}

void SdlGridRenderer::calculate_size() {
    Coord world_size = world.get_size();
    int window_x, window_y;
    SDL_GetWindowSize(window, &window_x, &window_y);
    int size_x = (int)(window_x/world_size.x);
    int size_y = (int)(window_y/world_size.y);
    cell_size = std::min(size_x, size_y);
    SDL_Log("Cell size : %i", cell_size);
}
