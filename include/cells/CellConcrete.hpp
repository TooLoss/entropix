#pragma once

class CellConcrete : public Cell {
public:
    CellConcrete() : Cell({ 150, 145, 134, 255 }) {};

    virtual void update(Coord pos, World& world) const override;
}
