#include <SDL3/SDL_log.h>
#include <algorithm>
#include "render/Camera.hpp"

Camera::Camera(World& world, SDL_Window* window, SDL_Renderer* renderer)
    : world(world), window(window), renderer(renderer), corner_start(0, 0), corner_end(world.get_size()) {
    zoom_end_x = (float)corner_end.x;
    zoom_end_y = (float)corner_end.y;
    refresh_rectangles();
};

void Camera::refresh_rectangles() {
    cell_size = calculate_size(this->get_size());
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

size_t Camera::calculate_size(Coord camera_size) {
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);
    int size_x = (int)(window_x/camera_size.x);
    int size_y = (int)(window_y/camera_size.y);
    return std::min(size_x, size_y);
}

Coord Camera::camera_to_screen_position(Coord pos) const {
    return Coord(pos.x * cell_size, pos.y * cell_size);
}

Coord Camera::camera_to_world_position(Coord pos) const {
    return Coord(pos.x + corner_start.x, pos.y + corner_start.y);
}

bool Camera::can_fit_cell(uint8_t new_size) {
    int win_x, win_y;
    SDL_GetWindowSize(this->window, &win_x, &win_y);
    float ratio_x = (float)win_x / new_size;
    float ratio_y = (float)win_y / new_size;
    return ratio_x > ratio_y ? win_y % new_size < new_size/4 : win_y % new_size < new_size/4;
}

Coord Camera::get_size() {
    return Coord(
        corner_end.x - corner_start.x,
        corner_end.y - corner_start.y
    );
}

Coord Camera::get_center() {
    Coord size = this->get_size();
    return Coord(size.x/2, size.y/2);
}

void Camera::zoom(int speed, float mouse_pos_x, float mouse_pos_y) {
    int win_x, win_y;
    SDL_GetWindowSize(this->window, &win_x, &win_y);

    float mouse_ratio_x = mouse_pos_x / (float)win_x;
    float mouse_ratio_y = mouse_pos_y / (float)win_y;

    float current_x = zoom_end_x - zoom_start_x;
    float current_y = zoom_end_y - zoom_start_y;

    float zoom_step_x = current_x * 0.1f * (float)speed;
    float zoom_step_y = current_y * 0.1f * (float)speed;

    zoom_start_x += zoom_step_x * mouse_ratio_x;
    zoom_end_x -= zoom_step_x * (1.0f - mouse_ratio_x);

    zoom_start_y += zoom_step_y * mouse_ratio_y;
    zoom_end_y -= zoom_step_y * (1.0f - mouse_ratio_y);

    Coord world_size = world.get_size();

    if (zoom_start_x < 0)
        zoom_start_x = 0;
    if (zoom_start_y < 0)
        zoom_start_y = 0;
    if (zoom_end_x > world_size.x)
        zoom_end_x = world_size.x;
    if (zoom_end_y > world_size.y)
        zoom_end_y = world_size.y;

    Coord camera_size(zoom_end_x - zoom_start_x, zoom_end_y - zoom_start_y);
    size_t new_cell_size = calculate_size(camera_size);
    if (can_fit_cell(new_cell_size)) {
        corner_start = Coord(zoom_start_x, zoom_start_y);
        corner_end = Coord(zoom_end_x, zoom_end_y);
        this->refresh_rectangles();
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[DEBUG] new cell size : %i",
                 unsigned(new_cell_size));
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
            // this is why is not same position as world.
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
