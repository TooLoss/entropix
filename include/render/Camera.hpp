#pragma once
#include "core/World.hpp"

class Camera {
private:
    World& world;
    std::vector<SDL_FRect> render_grid;
    size_t cell_size;
    SDL_Renderer* renderer;
    SDL_Window* window;

    Coord center;
    Coord camera_size;

public:
    Camera(World& world, SDL_Window* window, SDL_Renderer* renderer);

    Coord camera_to_world_pos(Coord pos);

    void add_zoom(int speed, float mouse_pos_x, float mouse_pos_y);
    void draw_canvas();
    void render();

    size_t get_cell_size();
};
