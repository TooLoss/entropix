#pragma once
#include "utils/Coord.hpp"
#include <functional>
#include <SDL3/SDL_events.h>

class GameState;

class Canva {
private:
    Coord pos;
    Coord size;

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
    virtual void mouse_action(SDL_Event* event, GameState& gamestate);

    void set_click_event(std::function<void()> func);
    void event_clicked();
};
