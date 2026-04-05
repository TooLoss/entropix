#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include "core/GameState.hpp"
#include "core/GameConst.hpp"
#include "core/CellRegistry.hpp"

GameState::GameState(SDL_Renderer *renderer, SDL_Window *window) :
    renderer(renderer),
    window(window),
    ui(nullptr) {};

GameState::~GameState() {}

void GameState::render() {
    if (ui) this->ui->render();
}

/*
* GameState_Play
*/

GameState_Play::GameState_Play(SDL_Renderer *renderer, SDL_Window *window) :
    GameState(renderer, window),
    world(GameConst::GRID_SIZE),
    camera(world, renderer)
{
    this->ui = std::make_unique<GameUI_Play>(renderer, window, *this, camera);
    bind_input_manager();
}

void GameState_Play::bind_input_manager() {
    input_manager.bind(SDLK_SPACE, ActionID::Pause, InputType::Keyboard,
                       [this]() { this->toogle_pause(); });
    input_manager.bind(SDLK_UP, ActionID::MoveUp, InputType::Keyboard,
                       [this]() { this->camera.translate(0, -1); });
    input_manager.bind(SDLK_DOWN, ActionID::MoveDown, InputType::Keyboard,
                       [this]() { this->camera.translate(0, 1); });
    input_manager.bind(SDLK_RIGHT, ActionID::MoveRight, InputType::Keyboard,
                       [this]() { this->camera.translate(1, 0); });
    input_manager.bind(SDLK_LEFT, ActionID::MoveLeft, InputType::Keyboard,
                       [this]() { this->camera.translate(-1, 0); });
}

void GameState_Play::toogle_pause() {
    SDL_Log("Paused");
    paused = !paused;
}

void GameState_Play::input_place(SDL_Event* event, CellID id, bool force) {
    uint8_t cell_size = camera.get_cell_size();
    Vector2<float> mouse = { event->button.x, event->button.y };
    Coord mouse_world_pos = camera.screen_to_world_tile(mouse);
    Pixel pixel;
    pixel.id = id;
    if (!world.is_out_of_range(mouse_world_pos) &&
        (force || world.is_empty(mouse_world_pos)))
        world.set_pixel(mouse_world_pos, pixel);
    SDL_Log("Pixel added position : %zu, %zu", mouse_world_pos.x, mouse_world_pos.y);
}

void GameState_Play::init() {
}

void GameState_Play::input(SDL_Event* event) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event->button.button == SDL_BUTTON_LEFT)
            this->input_place(event, CellID::SAND);
        else if (event->button.button == SDL_BUTTON_RIGHT)
            this->input_place(event, CellID::VOID, true);
    } else if (event->type == SDL_EVENT_KEY_DOWN) {
        this->input_manager.handle_event(*event, InputType::Keyboard);
    } else if (event->type == SDL_EVENT_MOUSE_WHEEL) {
        float mouse_x, mouse_y;
        uint32_t buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
        if (event->wheel.y > 0) {
            camera.zoom(1, Vector2<float>(0));
        } else if (event->wheel.y < 0) {
            camera.zoom(-1, Vector2<float>(0));
        }
    }
}

void GameState_Play::update() {
    if (!paused)
        this->world.refresh();
}
