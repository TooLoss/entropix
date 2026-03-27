#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include "core/GameState.hpp"
#include "core/GameConst.hpp"
#include "core/CellRegistry.hpp"

GameState::~GameState() {}

GameState_Play::GameState_Play(SDL_Renderer *renderer, SDL_Window *window) :
    GameState(renderer, window),
    world(GameConst::GRID_SIZE),
    camera(world, window, renderer) {}

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
        float mouse_x, mouse_y;
        uint32_t buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
        if (event->wheel.y > 0) {
            camera.zoom(1, mouse_x, mouse_y);
        } else if (event->wheel.y < 0) {
            camera.zoom(-1, mouse_x, mouse_y);
        }
    }
}

void GameState_Play::input_place(SDL_Event* event, CellID id, bool force) {
    uint8_t cell_size = camera.get_cell_size();
    const int mouse_x = static_cast<int>(event->button.x / cell_size);
    const int mouse_y = static_cast<int>(event->button.y / cell_size);
    Coord mouse_world_pos = camera.camera_to_world_pos(Coord(mouse_x, mouse_y));
    Pixel pixel;
    pixel.id = id;
    if (!world.is_out_of_range(mouse_world_pos) &&
        (force || world.is_empty(mouse_world_pos)))
        world.set_pixel(mouse_world_pos, pixel);
    SDL_Log("Pixel added position : %i, %i", mouse_x, mouse_y);
}

void GameState_Play::update() {
    if (!paused)
        this->world.refresh();
}
