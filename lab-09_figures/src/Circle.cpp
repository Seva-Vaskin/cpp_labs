#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y), radius(radius) {
    int label_length = std::strlen(label);
    char * tmp = new char[label_length + 1];
    std::strcpy(tmp, label);
    this->label = tmp;
}

Circle::~Circle() {
    delete[] label;
}

void Circle::print() const {
    printf("Circle ");
    Figure::print();
    printf(" radius = %d label = %s\n", radius, label);
}

bool Circle::is_inside(int x, int y) const {
    return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= radius * radius;
}

void Circle::zoom(int factor) {
    radius *= factor;
}


