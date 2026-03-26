#pragma once

template <typename T = int>
struct Coord {
    T x = 0;
    T y = 0;

    Coord(T x, T y) : x(x), y(y) {};

    Coord& operator+(const Coord& i) { x += i.x; y += i.y; return *this; }
    bool operator>=(T i) const { return (this->x >= i) && (this->y >= i); }
    bool operator>(T i) const { return (this->x > i) && (this->y > i); }
    bool operator==(T i) const { return (this->x == i) && (this->y == i); }
    bool operator==(const Coord& i) const { return (this->x == i.x) && (this->y == i.y); }
    bool operator!=(const Coord& other) const { return !(*this == other); }
    Coord operator*(T i) const { return Coord(this->x * i, this->y * i); }

    struct Iterator {
        T curX, curY, width;

        Coord operator*() const { return Coord(curX, curY); }

        Iterator& operator++() {
            curX++;
            if (curX >= width) { 
                curX = 0; 
                curY++; 
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            if (curY != other.curY) return true;
            return curX != other.curX;
        }
    };

    struct Range {
        T x, y;
        Iterator begin() const { return Iterator{0, 0, x}; }
        Iterator end() const { return Iterator{0, y, x}; }
    };

    Range all_points() const { return Range{x, y}; }

    T vector_to_index(Coord size) const { return size.x * y + x; }
};
