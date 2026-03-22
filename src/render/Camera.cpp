#include "render/Camera.hpp"

Camera::Camera(World& world) : world(world), corner_start(0, 0), corner_end(world.get_size()) {
    refresh_rectangles();
};

void Camera::refresh_rectangles() {
    calculate_size();
    Coord size = get_camera_size();
    render_grid.resize(size.x * size.y);
    for (int i = corner_start.x; i < corner_end.x; i++) {
        for (int j = corner_start.y; j < corner_start.y; j++) {
            Coord pos(i,j);
            Coord world_pos(i*cell_size, j*cell_size);
            SDL_FRect rect = {(float)world_pos.x, (float)world_pos.y,
                              (float)cell_size, (float)cell_size};
            render_grid[pos.vector_to_index(size)] = rect;
        }
    }
}

void Camera::calculate_size() {
    Coord camera_size = get_camera_size();
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);
    int size_x = (int)(window_x/camera_size.x);
    int size_y = (int)(window_y/camera_size.y);
    cell_size = std::min(size_x, size_y);
}

Coord Camera::get_camera_size() {
    return Coord(
        corner_end.x - corner_start.x,
        corner_end.y - corner_start.y
    );
}

void Camera::zoom(Coord center) {
    corner_end = Coord(corner_end.x - 1, corner_end.y - 1);
    corner_start = Coord(corner_start.x + 1, corner_start.y + 1);
    refresh_rectangles();
}
