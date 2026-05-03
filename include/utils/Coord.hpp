#pragma once
#include <stddef.h>
#include <ranges>

template <typename T>
struct Vector2 {
    T x = 0;
    T y = 0;

    Vector2(T x, T y) : x(x), y(y) {};
    Vector2(T scal) : x(scal), y(scal) {};
    Vector2() : x(0), y(0) {};

    // Convert Vector2
    template <typename U>
    Vector2(const Vector2<U>& other) 
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
    Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
    bool operator>=(T i) const { return (this->x >= i) && (this->y >= i); }
    bool operator>(T i) const { return (this->x > i) && (this->y > i); }
    bool operator==(T i) const { return (this->x == i) && (this->y == i); }
    bool operator==(const Vector2& i) const { return (this->x == i.x) && (this->y == i.y); }
    bool operator!=(const Vector2& other) const { return !(*this == other); }
    Vector2 operator*(T i) const { return Vector2(this->x * i, this->y * i); }

    struct Iterator {
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Vector2;
        using pointer = void; 
        using reference = Vector2;

        T curX, curY, width;

        Vector2 operator*() const { return Vector2(curX, curY); }

        Iterator& operator++() {
            if (++curX >= width) { 
                curX = 0; 
                curY++; 
            }
            return *this;
        }

        void operator++(int) { ++(*this); }

        bool operator==(const Iterator& other) const {
            return (curY == other.curY) && (curX == other.curX);
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    struct Range {
        T x, y;
        Iterator begin() const { return Iterator{0, 0, x}; }
        Iterator end() const { return Iterator{0, y, x}; }
    };

    Range all_points() const { return Range{x, y}; }

    T vector_to_index(Vector2 size) const { return size.x * y + x; }
    Vector2 index_to_vector(T index, T size_x) const {
        return Vector2(index % size_x, index / size_x);
    }
};

using Coord = Vector2<size_t>;
