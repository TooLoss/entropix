#include "core/World.hpp"
#include "render/TerminalRender.hpp"

int main(int argc, char *argv[]) {
    const Coord SIZE = {5, 5};

    std::unique_ptr<World> world = std::make_unique<World>(SIZE);
    std::unique_ptr<TerminalRender> render = std::make_unique<TerminalRender>(*world);

    Pixel sand = world->create_pixel_id(CellID::SAND);
    world->set_pixel({1, 1}, sand);
    render->print();
    world->refresh();
    render->print();
    world->refresh();
    world->refresh();
    world->refresh();
    world->refresh();
    world->refresh();
    render->print();

    return 0;
}
