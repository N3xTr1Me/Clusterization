#ifndef CLUSTERIZATION_TARGET_H
#define CLUSTERIZATION_TARGET_H

#include <stdexcept>

#include "point.h"


class ITarget {

public:

    virtual inline unsigned int get_size() const noexcept = 0;

    virtual void add_point(Point& point) = 0;

    virtual inline const Point& operator[](unsigned int index) const = 0;

    virtual ~ITarget() = default;

};


// Цель, т.е. кластер точек, находящихся рядом друг с другои на плоскости (Близость определяется как расстояния не более
// x_epsilon по оси X и y_espilon по оси Y).
class Target : public ITarget {

    // Реальное количество точек в цели
    unsigned int size = 0;

    Point point_group[POINT_LIMIT];

public:

    Target() : size(0), point_group() {};

    // Инициализация через первую точку
    explicit Target(Point& first) : size(1), point_group() {


        first.target_id = this;
        this->point_group[0] = first;
    }

    // Конструктор копирования
    Target(const Target& other) : point_group() {

        this->size = other.size;

        for (unsigned int i = 0; i < this->size; ++i) {
            this->point_group[i] = other.point_group[i];
            this->point_group[i].target_id = this;
        }

    }

    //------------------------------------------------------------------------------------------------------------------

    inline unsigned int get_size() const noexcept override { return this->size; };

    void add_point(Point& point) override {

        if (this->size >= POINT_LIMIT) {
            throw std::runtime_error("Point limit for this target reached!");
            // TODO: поправить на добавление ошибки в общий "стейт" программы
        }

        this->point_group[this->size++] = point;

    }

    //------------------------------------------------------------------------------------------------------------------

    inline const Point& operator[](unsigned int index) const override {

        if (index >= this->size) {
            throw std::runtime_error("index out of bounds: " +
                                     std::to_string(index) +
                                     " / " +
                                     std::to_string(this->size)
            );
            // TODO: +
        }

        return this->point_group[index];

    }

    Target& operator=(const Target& other) {

        // Проверка на "само-присвоение"
        if (this != &other) {

            this->size = other.size;

            for (unsigned int i = 0; i < this->size; ++i) {
                this->point_group[i] = other.point_group[i];
                this->point_group[i].target_id = this;
            }

        }
        return *this;

    }

    // Переопределение деструктора потому что полиморфизм...
    ~Target() override = default;

};


#endif //CLUSTERIZATION_TARGET_H
