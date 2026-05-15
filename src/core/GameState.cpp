#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <memory>
#include "core/GameState.hpp"
#include "core/GameConst.hpp"
#include "core/CellRegistry.hpp"

GameState::GameState(SDL_Renderer *renderer, SDL_Window *window) :
    renderer(renderer),
    window(window),
    ui(nullptr)
{
    SDL_GetWindowSize(window, &info.w, &info.h);
};

void GameState::render() {
    if (ui) this->ui->render();
}

void GameState::update() {}

void GameState::init() {}

void GameState::click_canvas(SDL_Event* event) {
    Coord hit(event->button.x, event->button.y);
    Canva* hit_canva;
    if (ui && (hit_canva = ui->get_canvas(hit))) {
        hit_canva->event_clicked();
    }
}

SDL_Renderer* GameState::get_renderer() {
    return this->renderer;
}

SDL_Window* GameState::get_window() {
    return this->window;
}

GameUI* GameState::get_gameui() {
    return ui.get();
}

Coord GameState::get_screen_size() {
    return Coord(info.w, info.h);
}

/*
* GameState_Play
*/

GameState_Play::GameState_Play(SDL_Renderer *renderer, SDL_Window *window) :
    GameState(renderer, window),
    world(GameConst::GRID_SIZE)
{
    // Create UI components
    camera.init(this, &world);
    cell_selection.init(this, &this->cell_selected);
    ui = std::make_unique<GameUI_Play>(renderer, window, *this, camera);

    // WindowLayout camera.layout{camera. 1};
    WindowLayout selection_layout{ cell_selection, 1 };
    Coord selection_layout_pos(3*info.w/4, 0);
    Coord selection_layout_size(info.w/4, info.h);
    ui->register_canva(selection_layout, selection_layout_size, selection_layout_pos);
    bind_input_manager();
    SDL_Log("GameState construction success");
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
    // input_manager.bind(SDL_BUTTON_LEFT, ActionID::Place, InputType::MouseButton,
    //                    [this]() { this->input_place(-1, 0); });
    // TODO pass location ?
    camera.set_click_event([this]() {
        this->input_place(&this->last_event, this->cell_selected, false);
    });
}

void GameState_Play::toogle_pause() {
    SDL_Log("Paused");
    paused = !paused;
}

void GameState_Play::input_place(SDL_Event* event, CellID id, bool force) {
    uint8_t cell_size = camera.get_cell_size();
    Vector2<float> mouse = { event->button.x, event->button.y };
    auto mouse_world_pos = camera.screen_to_world_tile(mouse);
    Pixel pixel;
    pixel.id = id;
    if (!world.is_out_of_range(mouse_world_pos)) {
        if (force || world.is_empty(mouse_world_pos)) {
            world.set_pixel(mouse_world_pos, pixel);
            SDL_Log("Pixel added position : %i, %i", mouse_world_pos.x, mouse_world_pos.y);
        }
    }
}

void GameState_Play::init() {
    cell_selected = CellID::SAND;
}

void GameState_Play::input(SDL_Event* event) {
    last_event = *event;
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        click_canvas(event);
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
