#ifndef CLUSTERIZATION_DOMAIN_H
#define CLUSTERIZATION_DOMAIN_H

#include "point.h"
#include <iostream>


class Domain {

    const unsigned int x_size;
    const unsigned int y_size;

    Point data[Y_LIMIT][X_LIMIT];

public:

    Domain() = default;
    explicit Domain(int data[Y_LIMIT][X_LIMIT]) : x_size(X_LIMIT), y_size(Y_LIMIT), data() {

        for (int y = 0; y < this->y_size; ++y) {
            for (int x = 0; x < this->y_size; ++x) {
                this->data[y][x] = Point(x, y, data[y][x]);
            }
        }

    }
    Domain(bool** data, unsigned int x_size, unsigned int y_size) : x_size(x_size), y_size(y_size) {

        for (int y = 0; y < this->y_size; ++y) {
            for (int x = 0; x < this->y_size; ++x) {
                this->data[y][x] = Point(x, y, data[y][x]);
            }
        }

    };

    unsigned int get_x_size() const { return this->x_size; };
    unsigned int get_y_size() const { return this->y_size; };

    Point* operator[](unsigned int index) { return this->data[index]; };

    ~Domain() = default;

};

#endif //CLUSTERIZATION_DOMAIN_H
