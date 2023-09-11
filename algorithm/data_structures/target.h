#ifndef CLUSTERIZATION_TARGET_H
#define CLUSTERIZATION_TARGET_H

#include "./Domain.h"

//TODO Заменить проброс ошибки на работу с общим стейтом


// Цель, т.е. кластер точек, находящихся рядом друг с другои на плоскости (Близость определяется как расстояния не более
// x_epsilon по оси X и y_espilon по оси Y).
class Target {

protected:

    // "Реальный" размер цели, т.е. количество входящих в нее точек
    unsigned int size = 0;

    Dot points[POINT_LIMIT];

public:

    Target() = default;

    explicit Target(Dot& first) : size(0), points() {

        this->points[this->size++] = first;

    }

    Target(const Target& other) {

        this->size = other.size;

        for (unsigned int i = 0; i < this->size; ++i) {
            this->points[i] = other.points[i];
        }

    }

    //------------------------------------------------------------------------------------------------------------------

    inline unsigned int get_size() const noexcept { return this->size; };

    inline void add_point(Point& point) {

        if (this->size >= POINT_LIMIT) {

            State::call().report(Errors::target_points_overflow);

            if (State::call().notification_mode()) {
                std::cerr << "Target is full! Cannot add more points.\n";
            }

            return;
        }

        this->points[this->size++] = Point::squeeze(point);
        point.target_id = this;

    }

    //------------------------------------------------------------------------------------------------------------------

    inline const Dot& operator[](unsigned int index) const {

        if (index >= POINT_LIMIT) {

            State::call().report(Errors::target_index_out_of_bounds);

            if (State::call().notification_mode()) {

                std::cerr << "Index out of range! Limit of points in target is: " +
                             std::to_string(POINT_LIMIT - 1) + "\n";

            }

            // Вернем последнюю точку
            return this->points[POINT_LIMIT - 1];
        }

        return this->points[index];
    }

    Target& operator=(const Target& other) {

        if (this != &other) {

            this->size = other.size;

            for (unsigned int i = 0; i < this->size; ++i) {
                this->points[i] = other.points[i];
            }

        }

        return *this;

    }

    ~Target() = default;
    
};


#endif //CLUSTERIZATION_TARGET_H
