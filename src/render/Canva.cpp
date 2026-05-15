#include "render/Canva.hpp"
#include "core/GameState.hpp"

Coord Canva::get_position() const {
    return pos;
}

Coord Canva::get_size() const {
    return size;
}

Coord Canva::get_canvas_location(Coord relative_pos) const {
    return pos + relative_pos;
}

void Canva::set_size(const Coord size) {
    this->size = size;
}

void Canva::set_position(const Coord pos) {
    this->pos = pos;
}

bool Canva::is_hit(const Coord hit) {
    Coord pos_start = this->pos;
    Coord pos_end = this->pos + this->size;
    bool in_x = pos_start.x <= hit.x && pos_end.x > hit.x;
    bool in_y = pos_start.y <= hit.y && pos_end.y > hit.y;
    return in_x && in_y;
}

void Canva::refresh_canva() {}

void Canva::render() {}

void Canva::set_click_event(std::function<void()> func) {
    click_event = func;
}

void Canva::event_clicked() {
    if (click_event)
        click_event();
}

void Canva::set_gamestate(GameState* state) {
    this->game_state = state;
}

SDL_Renderer* Canva::get_renderer() {
    return this->game_state ? this->game_state->get_renderer() : nullptr;
}

GameState* Canva::get_gamestate() {
    return this->game_state;
}

GameUI* Canva::get_gameui() {
    return this->game_state ? this->game_state->get_gameui() : nullptr;
}
