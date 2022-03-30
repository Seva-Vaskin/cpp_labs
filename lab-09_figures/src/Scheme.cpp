#include "Scheme.hpp"

Scheme::Scheme(int capacity) : capacity(capacity), size(0) {
    figures_ = new Figure*[capacity];
    std::memset(figures_, 0, sizeof(Figure*) * capacity);
}

Scheme::~Scheme() {
    for (int i = 0; i < size; i++)
        delete figures_[i];
    delete[] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    if (size == capacity)
        throw std::overflow_error("Too many figures in the scheme");
    figures_[size++] = fg;
}

void Scheme::remove_figure(int id) {
    int index = find_index_by_id(id);
    delete figures_[index];
    for (int i = index + 1; i < size; i++) {
        figures_[i - 1] = figures_[i];
    }
    size--;
}

void Scheme::print_all_figures() {
    for (int i = 0; i < size; i++)
        figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    int index = find_index_by_id(id);
    figures_[index]->zoom(factor);
}

int Scheme::find_index_by_id(int id) const {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (figures_[i]->get_id() == id)
            index = i;
    }
    if (index == -1)
        throw std::invalid_argument("No such id in the scheme");
    return index;
}

Figure *Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < size; i++) {
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    int index = find_index_by_id(id);
    figures_[index]->move(new_x, new_y);
}
