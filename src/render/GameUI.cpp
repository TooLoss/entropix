#include <SDL3/SDL_log.h>
#include <algorithm>
#include "render/GameUI.hpp"
#include "render/CellSelection.hpp"
#include "core/GameState.hpp"

GameUI::GameUI(SDL_Renderer *renderer, SDL_Window *window, GameState& gamestate) :
    renderer(renderer),
    window(window),
    gamestate(gamestate)
{
    init_ui();
}

void GameUI::register_canva(WindowLayout new_layout) {
    Canva& in_canvas = new_layout.canva.get();
    in_canvas.set_gameui(this);
    in_canvas.refresh_canva();

    auto it = std::upper_bound(layouts.begin(), layouts.end(), new_layout, 
        [](const WindowLayout& a, const WindowLayout& b) {
            return a.z_index < b.z_index;
        });

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
    for (auto &layout : layouts) {
        Canva &canva = layout.canva.get();
        if (canva.is_hit(hit)) {
            return canva.get_hit(hit);
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

GameState& GameUI::get_gamestate() {
    return this->gamestate;
}

/*
*   GameUI_Play
*/

GameUI_Play::GameUI_Play(SDL_Renderer *renderer, SDL_Window *window,
                         GameState &gamestate, Camera &camera, CellSelection &cell_selection) :
    GameUI(renderer, window, gamestate),
    camera(camera),
    cell_selection(cell_selection)
{
    init_ui();
}

void GameUI_Play::init_ui() {
    layouts.reserve(4);

    Coord screen = this->get_gamestate().get_screen_size();

    Coord cam_pos = Coord(0);
    Coord cam_size = Coord(3*screen.x/4, screen.y);
    WindowLayout cam_layout(camera);
    this->register_canva(cam_layout, cam_size, cam_pos);

    Coord selection_layout_pos(3*screen.x/4, 0);
    Coord selection_layout_size(screen.x/4, screen.y);
    WindowLayout selection_layout{ cell_selection };
    this->register_canva(selection_layout, selection_layout_size, selection_layout_pos);
}
