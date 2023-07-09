#ifndef CLUSTERIZATION_SOLUTION_H
#define CLUSTERIZATION_SOLUTION_H

#include "../data_structures/target.h"


class Solution {

    unsigned int size = 0;

    Target data[TARGET_LIMIT];

public:

    Solution() = default;

    Solution(Target data[TARGET_LIMIT], unsigned int size) : size(size) {

        for (unsigned int i = 0; i < this->size; ++i) {
            this->data[i] = data[i];
        }

    };

    unsigned int get_size() const { return this->size; };

    Target& operator[](unsigned int index) { return this->data[index]; };

    ~Solution() = default;

};

#endif //CLUSTERIZATION_SOLUTION_H
