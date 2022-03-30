#pragma once

#include "Figure.hpp"
#include <cstring>
#include <stdexcept>

class Scheme {
public:
    explicit Scheme(int capacity);

    ~Scheme();

    void push_back_figure(Figure *fg);

    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures();

    void zoom_figure(int id, int factor);

    Figure *is_inside_figure(int x, int y); // если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y);

protected:
    int find_index_by_id(int id) const;

private:
    Figure **figures_; // размер массива задается в конструкторе и больше не растет
    int capacity;
    int size;
};
