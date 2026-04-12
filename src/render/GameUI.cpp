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
    in_canvas.refresh_canva();
    this->layouts.push_back(new_layout);
}

void GameUI::register_canva(WindowLayout new_layout, Coord size, Coord pos) {
    Canva& in_canvas = new_layout.canva.get();
    in_canvas.set_size(size);
    in_canvas.set_position(pos);
    register_canva(new_layout);
}

Canva* GameUI::get_canvas(Coord hit) {
    Canva* hit_canva = nullptr;
    int max_zlayout = 0;
    for (auto layout : layouts) {
        Canva& canva = layout.canva.get();
        if (canva.is_hit(hit) && layout.z_index >= max_zlayout) {
            hit_canva = &canva;
            max_zlayout = layout.z_index;
        }
    }
    return hit_canva;
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
    WindowLayout cam_layout(camera);
    this->register_canva(cam_layout, cam_size, cam_pos);
}

void GameUI_Play::init_ui() {
    init_camera();
}

void GameUI_Play::render() {
    camera.render();
}
