#include <SDL3/SDL_log.h>
#include "render/GameUI.hpp"

GameUI::GameUI(SDL_Renderer *renderer, SDL_Window *window, GameState& gamestate) :
    renderer(renderer),
    window(window),
    gamestate(gamestate)
{
    init_ui();
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
    Coord pos = Coord(0);
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);
    Coord size = Coord(3*window_x/4, window_y);
    camera.set_size(size);
    camera.set_position(pos);
    camera.draw_grid();
    SDL_Log("UI camera redraw");
}

void GameUI_Play::init_ui() {
    init_camera();
}

void GameUI_Play::render() {
    camera.render();
}
