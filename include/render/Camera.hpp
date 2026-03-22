#pragma once
#include "core/World.hpp"

class Camera {
private:
    World& world;
    Coord corner_start, corner_end;
    std::vector<SDL_FRect> render_grid;
    uint8_t cell_size;
    SDL_Renderer* renderer;
    SDL_Window* window;

    void refresh_rectangles();
    void calculate_size();

public:
    Camera(World& world);

    Coord get_camera_size();
    void zoom(Coord center);
    void render();

};
