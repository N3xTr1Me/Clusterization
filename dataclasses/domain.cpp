#include "./domain.h"

Domain::Domain(Point* data, unsigned int x_size, unsigned int y_size): data(data), x_size(x_size), y_size(y_size) {}

Point &Domain::operator()(unsigned int x, unsigned int y) {
    if (x >= this->x_size) {
        throw std::out_of_range("");
    }

    if (y >= this->y_size) {
        throw std::out_of_range("");
    }

    return this->data[x * this->x_size + y];
};

