#pragma once
#include "core/World.hpp"

class Camera {
private:
    World& world;
    std::vector<SDL_FRect> render_grid;
    size_t cell_size;
    SDL_Renderer* renderer;
    SDL_Window* window;

    Vector2<float> center;
    float zoom;

public:
    Camera(World& world, SDL_Window* window, SDL_Renderer* renderer);

    void add_zoom(int speed, float mouse_pos_x, float mouse_pos_y);
    void draw_canvas();
    void render();
};
