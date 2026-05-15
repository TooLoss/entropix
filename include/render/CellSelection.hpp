#pragma once
#include <memory>
#include "render/Canva.hpp"
#include "render/Button.hpp"
#include "core/CellRegistry.hpp"

class CellSelection : public Canva {
private:
    size_t cell_per_col = 2;
    float gap = 20;
    float button_height = 50;
    std::vector<std::unique_ptr<Button>> buttons;
    std::vector<CellID> cell_ids;
    CellID* selected_cell;

public:
    CellSelection();

    void init(GameState* gamestate, CellID* bind_cell);

    virtual void refresh_canva() override;
    virtual void render() override;
    virtual Canva* get_hit(const Coord &hit) override;

    void set_color(SDL_Color color);
};
