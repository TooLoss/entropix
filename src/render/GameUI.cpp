#include "render/GameUI.hpp"

GameUI::GameUI(SDL_Renderer *renderer, SDL_Window *window) :
    renderer(renderer),
    window(window)
{
    this->init_ui();
    this->bind_inputs();
}

void GameUI::hander_ui_inputs(SDL_Event *event, InputType type) {
    input.handle_event(*event, type);
}

void GameUI::init_ui() {}

void GameUI::bind_inputs() {}

void GameUI::render() {}



void GameUI_Play::init_ui() {
    Coord pos = Coord(0);
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);
    Coord size = Coord((3*window_x)/4, window_y);
    camera = std::make_unique<Camera>(renderer, pos, size);
}

void GameUI_Play::bind_inputs() {
    input.bind(SDLK_UP, ActionID::MoveUp, InputType::Keyboard,
                       [this]() { this->camera->translate(0, -1); });
    input.bind(SDLK_DOWN, ActionID::MoveDown, InputType::Keyboard,
                       [this]() { this->camera->translate(0, 1); });
    input.bind(SDLK_RIGHT, ActionID::MoveRight, InputType::Keyboard,
                       [this]() { this->camera->translate(1, 0); });
    input.bind(SDLK_LEFT, ActionID::MoveLeft, InputType::Keyboard,
                       [this]() { this->camera->translate(-1, 0); });
}

void GameUI_Play::render() {}
