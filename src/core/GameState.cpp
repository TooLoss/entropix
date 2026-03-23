#include <SDL3/SDL_log.h>
#include "core/GameState.hpp"
#include "core/GameConst.hpp"
#include "core/CellRegistry.hpp"

GameState::~GameState() {}

GameState_Play::GameState_Play(SDL_Renderer *renderer, SDL_Window *window)
    : GameState(renderer, window), world(GameConst::GRID_SIZE), camera(world, window, renderer) {}

void GameState_Play::init() {
}

void GameState_Play::render() {
    camera.render();
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
    } else if (event->type == SDL_EVENT_MOUSE_WHEEL) {
        if (event->wheel.y > 0) {
            camera.zoom(1, Coord(0,0));
        } else if (event->wheel.y < 0) {
            camera.zoom(-1, Coord(0,0));
        }
    }
}

void GameState_Play::input_place(SDL_Event* event, CellID id, bool force) {
    uint8_t cell_size = camera.get_cell_size();
    const int mouse_x = static_cast<int>(event->button.x / cell_size);
    const int mouse_y = static_cast<int>(event->button.y / cell_size);
    Coord cam_pos = camera.get_camera_position();
    Coord mouse_pos(cam_pos.x + mouse_x, cam_pos.y + mouse_y);
    Pixel pixel = world.VOID_PIXEL;
    pixel.id = id;
    if (!world.is_out_of_range(mouse_pos) && (force || world.is_empty(mouse_pos)))
        world.set_pixel(mouse_pos, pixel);
    SDL_Log("Pixel added position : %i, %i", mouse_x, mouse_y);
}

void GameState_Play::update() {
    if (!paused)
        this->world.refresh();
}
