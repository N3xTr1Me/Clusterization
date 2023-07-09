#ifndef CLUSTERIZATION_TARGET_H
#define CLUSTERIZATION_TARGET_H

#include "point.h"


// Интерфейс цели.
class ITarget {

public:
    virtual unsigned int number_of_points() const = 0;

    virtual void add_point(Point& point) = 0;

    virtual Point* operator[](unsigned int index) const = 0;

    virtual ~ITarget() = default;

};


// Цель, т.е. кластер точек, находящихся рядом друг с другои на плоскости (Близость определяется как расстояния не более
// x_epsilon по оси X и y_espilon по оси Y).
class Target : public ITarget {

    Point* data[POINT_LIMIT];

    // "Реальный" размер, занятый валидными точками
    unsigned int size = 0;

public:

    Target() = default;

    Target(const Target& other) {
        this->size = other.size;

        for (unsigned int i = 0; i < this->size; ++i) {
            this->data[i] = other.data[i];
            this->data[i]->target_id = this;
        }
    };

    explicit Target(Point& first) : size(0), data() {
        first.target_id = this;
        this->data[this->size++] = &first;
    }

    unsigned int number_of_points() const override { return this->size; };

    void add_point(Point& point) override {
        if (this->size < POINT_LIMIT) {
            point.target_id = this;
            this->data[this->size++] = &point;
        }
    };

    Point* operator[](unsigned int index) const override { return this->data[index]; };

    Target& operator=(const Target& other) {
        this->size = other.size;

        for (unsigned int i = 0; i < this->size; ++i) {
            this->data[i] = other[i];
            this->data[i]->target_id = this;
        }

        return *this;
    }

    ~Target() override = default;
};


#endif //CLUSTERIZATION_TARGET_H
