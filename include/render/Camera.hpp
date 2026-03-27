#pragma once
#include "core/World.hpp"

class Camera {
private:
    World& world;
    std::vector<SDL_FRect> render_grid;
    size_t cell_size;
    SDL_Renderer* renderer;
    SDL_Window* window;

    Coord origin;
    Coord camera_size;
    Coord margins;

public:
    Camera(World& world, SDL_Window* window, SDL_Renderer* renderer);

    Coord camera_to_world_pos(Coord pos);
    Coord get_margin();

    void draw_canvas();
    void render();
    void zoom(int speed, float mouse_pos_x, float mouse_pos_y);

    size_t get_cell_size();
};
