#pragma once

#include <cstdio>

class Figure {
public:
    Figure(int id, int x, int y);

    virtual ~Figure() = default;

    virtual void print() const;

    virtual bool is_inside(int x, int y) const = 0;

    virtual void zoom(int factor) = 0;

    void move(int new_x, int new_y);

    int get_id() const;

protected:
    int id;
    int x;
    int y;
};
