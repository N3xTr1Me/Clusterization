#ifndef CLASTERIZATION_DOMAIN_H
#define CLASTERIZATION_DOMAIN_H


#include "./point.h"
#include <stdexcept>


class Domain {

    Point* data;

    unsigned int x_size = 0;
    unsigned int y_size = 0;

public:

    Domain() = default;
    Domain(Point* data, unsigned int x_size, unsigned int y_size);

    unsigned int get_x() const { return this->x_size; };
    unsigned int get_y() const { return this->y_size; };

    Point& operator()(unsigned int x, unsigned int y);

    ~Domain() = default;
};

#endif //CLASTERIZATION_DOMAIN_H
