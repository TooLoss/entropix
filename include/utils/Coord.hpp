#pragma once

struct Coord {
    int x;
    int y;

    Coord(int x, int y) : x(x), y(y) {};

    Coord& operator+(const Coord& i) { x += i.x; y += i.y; return *this; }
    bool operator>=(int i) const { return (this->x >= i) && (this->y >= i); }
    bool operator>(int i) const { return (this->x > i) && (this->y > i); }
    bool operator==(int i) const { return (this->x == i) && (this->y == i); }
    bool operator==(const Coord& i) const { return (this->x == i.x) && (this->y == i.y); }
    bool operator!=(const Coord& other) const { return !(*this == other); }
    Coord operator*(int i) const { return Coord(this->x * i, this->y * i); }

    struct Iterator {
        int curX, curY, width;

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
        int w, h;
        Iterator begin() const { return Iterator{0, 0, w}; }
        Iterator end() const { return Iterator{0, h, w}; }
    };

    Range all_points() const { return Range{x, y}; }

    int vector_to_index(Coord size) const { return size.x * y + x; }
};
