#ifndef CLUSTERIZATION_SOLUTION_H
#define CLUSTERIZATION_SOLUTION_H

#include "../data_structures/target.h"


// Решение, т.е. набор целей.
class Solution {

    // "Реальный" размер массива
    unsigned int size = 0;

    const unsigned int domain_x = 0;
    const unsigned int domain_y = 0;

    Target data[TARGET_LIMIT];

public:

    Solution() = default;

    Solution(Target data[TARGET_LIMIT], unsigned int size, unsigned int x_size, unsigned int y_size) :
    size(size), domain_x(x_size), domain_y(y_size) {

        for (unsigned int i = 0; i < this->size; ++i) {
            this->data[i] = data[i];
        }

    };

    unsigned int get_size() const { return this->size; };

    unsigned int get_x() const { return this->domain_x; };
    unsigned int get_y() const { return this->domain_y; };

    Target& operator[](unsigned int index) { return this->data[index]; };

    ~Solution() = default;

};

#endif //CLUSTERIZATION_SOLUTION_H
