#pragma once
#include <memory>
#include "render/Canva.hpp"
#include "render/Button.hpp"

class CellSelection : public Canva {
private:
    size_t cell_per_col = 2;
    float gap = 20;
    float button_height = 50;
    std::vector<std::unique_ptr<Button>> buttons;

public:
    using Canva::Canva;

    virtual void refresh_canva() override;
    virtual void render() override;

    void set_color(SDL_Color color);
};
