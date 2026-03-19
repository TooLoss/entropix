#include <SDL3/SDL_log.h>
#include "core/GameState.hpp"
#include "core/GameConst.hpp"
#include "core/CellRegistry.hpp"

GameState::~GameState() {}





void GameState_Play::calculate_size() {
    Coord world_size = world->get_size();
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);
    int size_x = (int)(window_x/world_size.x);
    int size_y = (int)(window_y/world_size.y);
    cell_size = std::min(size_x, size_y);
}

void GameState_Play::create_grid() {
    Coord size = this->world->get_size();
    render_grid.resize(size.x * size.y);
    for (int i = size.x - 1; i >= 0; i--) {
        for (int j = size.y - 1; j >= 0; j--) {
            Coord pos(i,j);
            Coord world_pos(i*cell_size, j*cell_size);
            SDL_FRect rect = {(float)world_pos.x, (float)world_pos.y,
                              (float)cell_size, (float)cell_size};
            render_grid[pos.vector_to_index(size)] = rect;
        }
    }
}

void GameState_Play::init() {
    this->world = std::make_shared<World>(GameConst::GRID_SIZE);
    calculate_size();
    create_grid();
}

void GameState_Play::render() {
    Coord size = this->world->get_size();
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            Coord pos(i, j);
            Pixel pixel = world->get_pixel(pos);
            const Cell& cell = world->get_registry().get(pixel.id);
            size_t index = pos.vector_to_index(size);
            cell.render(pos, *world, renderer, &render_grid[index]);
        }
    }
    SDL_RenderPresent(renderer);
}

void GameState_Play::input(SDL_Event* event) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event->button.button == SDL_BUTTON_LEFT)
            this->input_place(event, CellID::SAND);
        else if (event->button.button == SDL_BUTTON_RIGHT)
            this->input_place(event, CellID::VOID, true);
    } else if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_SPACE)
            paused = !paused;
    }
}

void GameState_Play::input_place(SDL_Event* event, CellID id, bool force) {
    const int mouse_x = static_cast<int>(event->button.x / cell_size);
    const int mouse_y = static_cast<int>(event->button.y / cell_size);
    Coord mouse_pos(mouse_x, mouse_y);
    Pixel pixel = world->VOID_PIXEL;
    pixel.id = id;
    if (!world->is_out_of_range(mouse_pos) && (force || world->is_empty(mouse_pos)))
        world->set_pixel(mouse_pos, pixel);
    SDL_Log("Pixel added position : %i, %i", mouse_x, mouse_y);
}

void GameState_Play::update() {
    if (!paused)
        this->world->refresh();
}
