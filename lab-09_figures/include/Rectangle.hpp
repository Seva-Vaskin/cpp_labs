#pragma once

#include "Figure.hpp"
#include <cstdio>
#include <cmath>

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);

    ~Rectangle() override;

    void print() const override;

    bool is_inside(int x, int y) const override;

    void zoom(int factor) override;

protected:
    int width;
    int height;
};
