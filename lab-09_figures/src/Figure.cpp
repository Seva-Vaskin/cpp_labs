#include "Figure.hpp"

Figure::Figure(int id, int x, int y) : id(id), x(x), y(y) {}

void Figure::move(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

int Figure::get_id() const {
    return id;
}

void Figure::print() const {
    printf("%d: x = %d y = %d", id, x, y);
}