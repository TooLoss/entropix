#pragma once
#include "utils/Coord.hpp"
#include <functional>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

class GameState;
class GameUI;

class Canva {
private:
    Coord pos;
    Coord size;
    GameState* game_state = nullptr;
    GameUI* game_ui = nullptr;

    std::function<void()> click_event;

public:
    Canva(Coord pos, Coord size) : pos(pos), size(size) {}
    Canva() : pos(0), size(0) {}

    Coord get_position() const;
    Coord get_size() const;
    Coord get_canvas_location(Coord relative_pos) const;

    void set_size(const Coord size);
    void set_position(const Coord pos);

    bool is_hit(const Coord hit);

    virtual void refresh_canva();
    virtual void render();

    void set_click_event(std::function<void()> func);
    void event_clicked();

    void set_gamestate(GameState* state);
    void set_gameui(GameUI* state);

    SDL_Renderer* get_renderer();
    GameState* get_gamestate();
    GameUI* get_gameui();
};
