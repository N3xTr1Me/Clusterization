#ifndef CLUSTERIZATION_DOMAIN_H
#define CLUSTERIZATION_DOMAIN_H

#include <stdexcept>

#include "../configuration/config.h"
#include "./point.h"


// Непосредственно двумерная плоскость с точками на ней.
class Domain {

protected:

    // Размеры области
    unsigned int x_size = X_LIMIT;
    unsigned int y_size = Y_LIMIT;

    // Количество "реальных" (валидных) точек
    unsigned int number_of_points = 0;

    // "Реальные" точки, т.е. валидные
    Point real_points[TARGET_LIMIT * POINT_LIMIT];

    // Рассматриваемая область, как с валидными (реальными) точками, так и с невалидными (пустые указатели)
    Point* plane[Y_LIMIT][X_LIMIT] = {nullptr};

public:

    Domain() = default;

    // Конструктор области фиксированного размера
    explicit Domain(int points[Y_LIMIT][X_LIMIT]) : x_size(X_LIMIT), y_size(Y_LIMIT), plane(), number_of_points()
    {

        for (int y = 0; y < this->y_size; ++y) {
            for (int x = 0; x < this->x_size; ++x) {

                if (points[y][x] > 0) {

                    this->real_points[this->number_of_points] = Point(x, y);
                    this->plane[y][x] = &this->real_points[this->number_of_points];

                    this->number_of_points++;

                }

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

        unsigned int i = 0;

        this->x_size = x_size;
        this->y_size = y_size;

        for (int y = 0; y < y_size; ++y) {
            for (int x = 0; x < x_size; ++x) {

                if (points[y][x] > 0) {

                    this->real_points[i] = Point(x, y);
                    this->plane[y][x] = &this->real_points[i];

                    i++;

                }

            }
        }

    }

    // Конструктор копирования
    Domain(Domain& other) {

        this->x_size = other.x_size;
        this->y_size = other.y_size;

        this->number_of_points = other.number_of_points;

        for (unsigned int i = 0; i < this->number_of_points; ++i) {

            this->real_points[i] = other.real_points[i];
            this->plane[real_points[i].y][real_points[i].x] = &real_points[i];

        }

    }

    //------------------------------------------------------------------------------------------------------------------

    // Методы "геттеры"

    unsigned int get_x_size() const { return this->x_size; };
    unsigned int get_y_size() const { return this->y_size; };

    // получение точки из массива
    Point* get_point(int x, int y) {

        if (y >= this->y_size) {
            State::call().report(Errors::domain_Y_out_of_bounds);

            if (State::call().notification_mode()) {

                std::cerr << "Y index is out of bounds: " + std::to_string(y) +
                             " out of " + std::to_string(this->y_size) << "\n";

            }

            return nullptr;
        }

        if (x >= this->x_size) {
            State::call().report(Errors::domain_X_out_of_bounds);

            if (State::call().notification_mode()) {

                std::cerr << " index is out of bounds: " + std::to_string(x) +
                             " out of " + std::to_string(this->x_size) << "\n";

            }

            return nullptr;
        }

        return this->plane[y][x];

    }

    //------------------------------------------------------------------------------------------------------------------

    Domain& operator=(Domain other) {

        if (this != &other) {

            this->x_size = other.x_size;
            this->y_size = other.y_size;

            this->number_of_points = other.number_of_points;

            for (unsigned int i = 0; i < this->number_of_points; ++i) {

                this->real_points[i] = other.real_points[i];
                this->plane[real_points[i].y][real_points[i].x] = &real_points[i];

            }

        }

        return *this;
    }

    virtual ~Domain() = default;

};


#endif //CLUSTERIZATION_DOMAIN_H
