#include <SDL3/SDL_log.h>
#include "render/GameUI.hpp"

GameUI::GameUI(SDL_Renderer *renderer, SDL_Window *window, GameState& gamestate) :
    renderer(renderer),
    window(window),
    gamestate(gamestate)
{
    init_ui();
}

void GameUI::register_canva(WindowLayout new_layout) {
    new_layout.canva.set_size(new_layout.size);
    new_layout.canva.set_position(new_layout.position);
    new_layout.canva.refresh_canva();
    this->layout.push_back(new_layout);
}

void GameUI::init_ui() {}

void GameUI::render() {}

/*
*   GameUI_Play
*/

GameUI_Play::GameUI_Play(SDL_Renderer *renderer, SDL_Window *window,
                         GameState &gamestate, Camera &camera) :
    GameUI(renderer, window, gamestate),
    camera(camera)
{
    init_ui();
}

void GameUI_Play::init_camera() {
    layout.reserve(2);

    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);

    Coord cam_pos = Coord(0);
    Coord cam_size = Coord(3*window_x/4, window_y);
    this->register_canva({ camera, cam_size, cam_pos });
    SDL_Log("UI camera redraw");
}

void GameUI_Play::init_ui() {
    init_camera();
}

void GameUI_Play::render() {
    camera.render();
}
