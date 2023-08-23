#ifndef CLUSTERIZATION_DOMAIN_H
#define CLUSTERIZATION_DOMAIN_H

#include "point.h"
#include <iostream>


// Непосредственно двумерная плоскость с точками на ней.
class Domain {

    unsigned int x_size = 0;
    unsigned int y_size = 0;

    Point data[Y_LIMIT][X_LIMIT];

public:

    Domain() = default;

    // Создание плоскости из массива константных размеров
    explicit Domain(int data[Y_LIMIT][X_LIMIT]) : x_size(X_LIMIT), y_size(Y_LIMIT), data() {

        for (int y = 0; y < this->y_size; ++y) {
            for (int x = 0; x < this->x_size; ++x) {
                this->data[y][x] = Point(x, y, data[y][x]);
            }
        }

    }

    // Создание плоскости из массива произвольных размеров
    Domain(int** data, unsigned int x_size, unsigned int y_size) : x_size(x_size), y_size(y_size) {

        for (int y = 0; y < this->y_size; ++y) {
            for (int x = 0; x < this->x_size; ++x) {
                this->data[y][x] = Point(x, y, data[y][x]);
            }
        }

    };

    // get-методы для размеров плоскости
    unsigned int get_x_size() const { return this->x_size; };
    unsigned int get_y_size() const { return this->y_size; };

    void reassign(unsigned int x, unsigned y, ITarget* id) {
            this->data[y][x].target_id = id;
    };

    Point* operator[](unsigned int index) { return this->data[index]; };

    ~Domain() = default;

};

#endif //CLUSTERIZATION_DOMAIN_H
