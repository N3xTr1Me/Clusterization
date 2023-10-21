#ifndef CLUSTERIZATION_SOLUTION_H
#define CLUSTERIZATION_SOLUTION_H

#include "./target.h"


// Решение задачи, т.е. набор целей, найденных алгоритмом
class Solution {

protected:

    // "Реальный" размер массива
    unsigned int size = 0;

    // Массив целей
    Target targets[TARGET_LIMIT];

public:

    Solution() : targets() {};

    Solution(Target data[TARGET_LIMIT], unsigned int size) {

        if (size > TARGET_LIMIT) {
            
            State::call().report(
                Errors::solution_size_limit_exceeded,
                "Solution size: " + std::to_string(size) + " exceeds size limit of: " + std::to_string(TARGET_LIMIT)
            );

            size = TARGET_LIMIT;

        }

        this->size = size;

        for (unsigned int i = 0; i < this->size; ++i) {
            this->targets[i] = data[i];
        }

    }

    Solution(const Solution& other) {

        this->size = other.size;

        for (unsigned int i = 0; i < this->size; ++i) {
            this->targets[i] = other.targets[i];
        }

    }

    //------------------------------------------------------------------------------------------------------------------

    inline unsigned int get_size() const noexcept { return this->size; };

    //------------------------------------------------------------------------------------------------------------------

    inline const Target& operator[](unsigned int index) { return this->targets[index]; };

    Solution& operator=(const Solution& other) {

        if (this != &other) {

            this->size = other.size;

            for (unsigned int i = 0; i < this->size; ++i) {
                this->targets[i] = other.targets[i];
            }

        }

        return *this;

    }

    ~Solution() = default;

};

#endif //CLUSTERIZATION_SOLUTION_H
