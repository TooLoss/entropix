#include <SDL3/SDL_log.h>
#include "render/Camera.hpp"

Camera::Camera(World& world, SDL_Window* window, SDL_Renderer* renderer)
    : world(world), window(window), renderer(renderer), corner_start(1, 1), corner_end(world.get_size()) {
    refresh_rectangles();
};

void Camera::refresh_rectangles() {
    calculate_size();
    Coord size = this->get_size();
    render_grid.resize(size.x * size.y);
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            Coord camera_pos(i,j);
            Coord world_pos = camera_to_world_position(camera_pos);
            Coord screen_pos = camera_to_screen_position(camera_pos);
            SDL_FRect rect = {(float)screen_pos.x, (float)screen_pos.y,
                              (float)cell_size, (float)cell_size};
            render_grid[camera_pos.vector_to_index(size)] = rect;
        }
    }
}

void Camera::calculate_size() {
    Coord camera_size = this->get_size();
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);
    int size_x = (int)(window_x/camera_size.x);
    int size_y = (int)(window_y/camera_size.y);
    cell_size = std::min(size_x, size_y);
    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Cell render size : %i", unsigned(cell_size)); 
}

Coord Camera::camera_to_screen_position(Coord pos) const {
    return Coord(pos.x * cell_size, pos.y * cell_size);
}

Coord Camera::camera_to_world_position(Coord pos) const {
    return Coord(pos.x + corner_start.x, pos.y + corner_start.y);
}

Coord Camera::get_size() {
    return Coord(
        corner_end.x - corner_start.x,
        corner_end.y - corner_start.y
    );
}

void Camera::zoom(int speed, Coord mouse_pos) {
    if (corner_end.x > corner_start.x && corner_end.y > corner_start.y) {
        corner_end = Coord(corner_end.x - speed, corner_end.y - speed);
        corner_start = Coord(corner_start.x + speed, corner_start.y + speed);
        refresh_rectangles();
    }
}

void Camera::render() {
    Coord camera_size = this->get_size();
    Coord world_size = world.get_size();
    for (int i = 0; i < camera_size.x; i++) {
        for (int j = 0; j < camera_size.y; j++) {
            Coord camera_pos(i, j);
            Coord world_pos = camera_to_world_position(camera_pos);
            Pixel pixel = world.get_pixel(world_pos);
            const Cell& cell = world.get_registry().get(pixel.id);
            // Render rectangles are optimised to be shown only if it's on screen.
            size_t render_index = camera_pos.vector_to_index(camera_size);
            cell.render(world_pos, world, renderer, &render_grid[render_index]);
        }
    }
    SDL_RenderPresent(renderer);
}

uint8_t Camera::get_cell_size() const {
    return cell_size;
}

Coord Camera::get_camera_position() const {
    return corner_start;
}
