#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const {
    printf("Rectangle ");
    Figure::print();
    printf(" width = %d height = %d\n", width, height);
}

bool Rectangle::is_inside(int x, int y) const {
    return 2 * abs(x - this->x) <= width && 2 * abs(y - this->y) <= height;
}

void Rectangle::zoom(int factor) {
    height *= factor;
    width *= factor;
}

Rectangle::~Rectangle() = default;


