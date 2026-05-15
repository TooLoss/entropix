#pragma once
#include "render/Canva.hpp"

class Button : public Canva {
private:
    SDL_FRect button_rect;
    SDL_Color button_color;

public:
    Button() {};

    virtual void refresh_canva() override;
    virtual void render() override;

    void set_color(SDL_Color color);
};
