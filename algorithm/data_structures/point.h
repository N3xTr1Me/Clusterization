#ifndef CLUSTERIZATION_POINT_H
#define CLUSTERIZATION_POINT_H


#include "../configuration/state_handler.h"


class Target;


// Точка на плоскости
struct Dot {

    //Координаты на плоскости
    int x = 0;
    int y = 0;

    //------------------------------------------------------------------------------------------------------------------

    Dot() = default;
    Dot(int x, int y) : x(x), y(y) {};

    // Конструктор копирования
    Dot(const Dot& other) {

        this->x = other.x;
        this->y = other.y;
    }

    //------------------------------------------------------------------------------------------------------------------

    // Оператор присвоения копированием
    Dot& operator=(const Dot& other) {

        if (this != &other) {

            this->x = other.x;
            this->y = other.y;
        }

        return *this;
    }

    ~Dot() = default;

};


// Точка на плоскости
struct Point : public Dot {

    // Указатель на цель (кластер) к которой принадлежит данная точка
    Target* target_id = nullptr;

    //------------------------------------------------------------------------------------------------------------------

    Point() = default;

    Point(int x, int y) : Dot(x, y), target_id(nullptr) {};

    // Конструктор копирования
    Point(const Point& other)  : Dot(other) {
        this->target_id = other.target_id;
    }

    //------------------------------------------------------------------------------------------------------------------

    // Сжатие точки для хранения в целях
    inline static Dot squeeze(const Point& original) { return {original.x, original.y}; }

    //------------------------------------------------------------------------------------------------------------------

    // Оператор присвоения копированием
    Point& operator=(const Point& other) {

        if (this != &other) {
            this->target_id = other.target_id;

            this->x = other.x;
            this->y = other.y;
        }

        return *this;
    }

};

#endif //CLUSTERIZATION_POINT_H
