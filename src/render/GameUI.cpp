#include <SDL3/SDL_log.h>
#include <algorithm>
#include "render/GameUI.hpp"

GameUI::GameUI(SDL_Renderer *renderer, SDL_Window *window, GameState& gamestate) :
    renderer(renderer),
    window(window),
    gamestate(gamestate)
{
    init_ui();
}

void GameUI::register_canva(WindowLayout new_layout) {
    auto it = std::upper_bound(layouts.begin(), layouts.end(), new_layout, 
        [](const WindowLayout& a, const WindowLayout& b) {
            return a.z_index < b.z_index;
        });
    Canva& in_canvas = new_layout.canva.get();
    in_canvas.refresh_canva();
    this->layouts.insert(it, new_layout);
}

void GameUI::register_canva(WindowLayout new_layout, Coord size, Coord pos) {
    Canva& in_canvas = new_layout.canva.get();
    in_canvas.set_size(size);
    in_canvas.set_position(pos);
    register_canva(new_layout);
}

Canva* GameUI::get_canvas(Coord hit) {
    // Already sort by z_index
    Canva* hit_canva = nullptr;
    for (auto layout : layouts) {
        Canva& canva = layout.canva.get();
        if (canva.is_hit(hit)) {
            return &canva;
        }
    }
    return nullptr;
}

void GameUI::init_ui() {}

void GameUI::render() {
    for (auto& layout : layouts) {
        layout.canva.get().render();
    }
}

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
