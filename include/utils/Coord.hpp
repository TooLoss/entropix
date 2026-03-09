#pragma once

namespace utils {

struct Coord {
    int x;
    int y;

    Coord(int x, int y) : x(x), y(y) {};

    Coord& operator+(const Coord& i) { x += i.x; y += i.y; return *this; }
    bool operator>=(int i) const { return (this->x >= i) && (this->y >= i); }
    bool operator>(int i) const { return (this->x > i) && (this->y > i); }
    bool operator==(int i) const { return (this->x == i) && (this->y == i); }
    bool operator==(const Coord& i) const { return (this->x == i.x) && (this->y == i.y); }
    Coord operator*(int i) const { return Coord(this->x * i, this->y * i); }
};


}
