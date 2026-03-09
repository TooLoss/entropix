#pragma once

namespace entities {

class Cell {
private:
public:
    virtual void update();
    virtual void render() const;
};

}
