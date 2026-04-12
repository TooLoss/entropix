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
    Canva& in_canvas = new_layout.canva.get();
    in_canvas.set_size(new_layout.size);
    in_canvas.set_position(new_layout.position);
    in_canvas.refresh_canva();
    this->layouts.push_back(new_layout);
}

Canva* GameUI::get_canvas(Coord pos) {
    for (auto layout : layouts) {
        Coord pos_begin(canva.position);
        Coord pos_end(canva.position + canva.size);
        if ();
    }
    return nullptr;
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
    layouts.reserve(2);

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
