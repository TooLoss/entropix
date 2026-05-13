#include "render/CellSelection.hpp"
#include "render/GameUI.hpp"
#include "core/CellRegistry.hpp"
#include <SDL3/SDL_log.h>

void CellSelection::refresh_canva() {
    const Coord screen_size = this->get_size();
    const Coord relative_pos = this->get_position();
    const size_t cell_count = static_cast<size_t>(CellID::COUNT);
    SDL_Log("Cell %zu", cell_count);

    const float screen_w = static_cast<float>(screen_size.x);
    const float f_gap = static_cast<float>(gap);
    const float f_button_h = static_cast<float>(button_height);

    float button_w = (screen_w - ((static_cast<float>(cell_per_col) + 1.0f) * f_gap)) / static_cast<float>(cell_per_col);

    if (button_w < 0) button_w = 0;

    size_t row_count = (cell_count + cell_per_col - 1) / cell_per_col;
    Coord grid_size(cell_per_col, row_count);

    std::vector<std::unique_ptr<Button>> next_buttons;
    next_buttons.reserve(cell_count); 

    auto cell_range = std::views::take(grid_size.all_points(), cell_count);
    for (auto l : cell_range) {
        auto button = std::make_unique<Button>(this->get_gamestate());
        button->set_color({ 255, 255, 0, 255 });

        float fx = f_gap + ((button_w + f_gap) * static_cast<float>(l.x));
        float fy = f_gap + ((f_button_h + f_gap) * static_cast<float>(l.y));

        size_t final_x = relative_pos.x + static_cast<size_t>(fx);
        size_t final_y = relative_pos.y + static_cast<size_t>(fy);

        button->set_position(Coord(final_x, final_y));
        button->set_size(Coord(static_cast<size_t>(button_w), button_height));
        size_t cell_id = l.vector_to_index(grid_size);
        SDL_Log("Cell id : %zu", cell_id);
        CellID button_cell = static_cast<CellID>(cell_id);
        button->set_click_event([this, button_cell](){ this->selected_cell = button_cell; });
        button->refresh_canva();
        if (button)
            get_gameui()->register_canva(WindowLayout(*button));

        next_buttons.push_back(std::move(button));
    }

    this->buttons = std::move(next_buttons);

    SDL_Log("Canvas refreshed: %zu buttons created.", buttons.size());
}

void CellSelection::render() {
    for (auto& button : buttons) {
        button->render();
    }
}
