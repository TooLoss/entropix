#include "render/GameUI.hpp"

GameUI::GameUI(SDL_Renderer *renderer, SDL_Window *window, GameState& gamestate) :
    renderer(renderer),
    window(window),
    gamestate(gamestate)
{
    // this->init_ui();
}

void GameUI::hander_ui_inputs(SDL_Event *event, InputType type) {
    input.handle_event(*event, type);
}

void GameUI::init_ui() {}

void GameUI::render() {}

/*
*   GameUI_Play
*/

GameUI_Play::GameUI_Play(SDL_Renderer *renderer, SDL_Window *window,
                         GameState &gamestate, Camera &camera) :
    GameUI(renderer, window, gamestate),
    camera(camera) {}

void GameUI_Play::init_camera() {
    Coord pos = Coord(0);
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);
    Coord size = Coord((3*window_x)/4, window_y);
    camera.set_size(size);
    camera.set_position(pos);
}

void GameUI_Play::init_ui() {
    init_camera();
}

void GameUI_Play::render() {
    camera.render();
}
