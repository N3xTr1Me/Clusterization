#ifndef CLUSTERIZATION_DOMAIN_H
#define CLUSTERIZATION_DOMAIN_H

#include <stdexcept>

#include "../configuration/config.h"
#include "./point.h"


// Непосредственно двумерная плоскость с точками на ней.
class Domain {

protected:

    // Размеры области
    unsigned int x_size = 0;
    unsigned int y_size = 0;

    // Массив точек
    Point plane[Y_LIMIT][X_LIMIT];

//    Point[POINT_LIMIT];
//
//    Point* _plane[Y_LIMIT][X_LIMIT];

public:

    Domain() = default;

    // Конструктор области фиксированного размера
    explicit Domain(int points[Y_LIMIT][X_LIMIT]) : x_size(X_LIMIT), y_size(Y_LIMIT), plane()
    {

        for (int y = 0; y < this->y_size; ++y) {
            for (int x = 0; x < this->x_size; ++x) {
                this->plane[y][x] = Point(x, y, points[y][x] > 0);
            }
        }

    }

    // Создание области "произвольного" размера
    Domain(int** points, unsigned int x_size, unsigned int y_size) : plane()
    {

        if (x_size > X_LIMIT) {
            State::call().report(Errors::domain_X_border_breach);

            if (State::call().notification_mode()) {
                std::cerr << "X-axis size exceeds limit of " + std::to_string(X_LIMIT) << "\n";
            }

            // Если размер больше допустимого, то делаем его равным пороговому значению
            x_size = X_LIMIT;
        }

        if (y_size > Y_LIMIT) {
            State::call().report(Errors::domain_Y_border_breach);

            if (State::call().notification_mode()) {
                std::cerr << "Y-axis size exceeds limit of " + std::to_string(X_LIMIT) << "\n";
            }

            // Если размер больше допустимого, то делаем его равным пороговому значению
            y_size = Y_LIMIT;
        }

        this->x_size = x_size;
        this->y_size = y_size;

        for (int y = 0; y < y_size; ++y) {
            for (int x = 0; x < x_size; ++x) {
                this->plane[y][x] = Point(x, y, points[y][x] > 0);
            }
        }

    }

    // Конструктор копирования
    Domain(Domain& other) {

        this->x_size = other.x_size;
        this->y_size = other.y_size;

        for (int y = 0; y < this->y_size; ++y) {
            for (int x = 0; x < this->x_size; ++x) {
                this->plane[y][x] = other[y][x];
            }
        }

    }

    //------------------------------------------------------------------------------------------------------------------

    // Методы "геттеры"

    unsigned int get_x_size() const { return this->x_size; };
    unsigned int get_y_size() const { return this->y_size; };

    // Оператор обращения к массиву (точек)
    Point* operator[](unsigned int index) {

        if (index >= this->y_size) {
            State::call().report(Errors::domain_index_out_of_bounds);

            if (State::call().notification_mode()) {

                std::cerr << "Index is out of bounds: " + std::to_string(index) +
                             " out of " + std::to_string(this->y_size) << "\n";

            }

            return nullptr;
        }

        return this->plane[index];

    }

    //------------------------------------------------------------------------------------------------------------------

    Domain& operator=(Domain other) {

        if (this != &other) {

            this->x_size = other.x_size;
            this->y_size = other.y_size;

            for (int y = 0; y < this->y_size; ++y) {
                for (int x = 0; x < this->x_size; ++x) {
                    this->plane[y][x] = other[y][x];
                }
            }

        }

        return *this;
    }

    virtual ~Domain() = default;

};


#endif //CLUSTERIZATION_DOMAIN_H
