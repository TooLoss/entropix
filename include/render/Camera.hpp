#pragma once
#include "core/World.hpp"

class Camera {
private:
    World& world;
    Coord corner_start, corner_end;
    std::vector<SDL_FRect> render_grid;
    size_t cell_size;
    SDL_Renderer* renderer;
    SDL_Window* window;

    float zoom_start_x, zoom_start_y, zoom_end_x, zoom_end_y = 0;
    float offset_x, offset_y;

    void refresh_rectangles();
    size_t calculate_size(Coord camera_size);
    Coord camera_to_screen_position(Coord pos) const;
    Coord camera_to_world_position(Coord pos) const;
    bool can_fit_cell(uint8_t new_size);

public:
    Camera(World& world, SDL_Window* window, SDL_Renderer* renderer);

    Coord get_size();
    Coord get_center();
    void zoom(int speed, float mouse_pos_x, float mouse_pos_y);
    void render();
    uint8_t get_cell_size() const;
    Coord get_camera_position() const;

};
