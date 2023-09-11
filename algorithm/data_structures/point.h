#ifndef CLUSTERIZATION_POINT_H
#define CLUSTERIZATION_POINT_H


#include "../configuration/state_handler.h"


class Target;


// Точка на плоскости
struct Dot {

    //Координаты на плоскости
    int x = 0;
    int y = 0;

    // Флаг, определяющий будет ли данная точка рассмотрена алгоритмом (т.е. есть ли в ней что-либо)
    bool valid = false;

    Dot() = default;
    Dot(int x, int y) : x(x), y(y), valid(false) {};
    Dot(int x, int y, bool valid) : x(x), y(y), valid(valid) {};

    // Конструктор копирования
    Dot(const Dot& other) {
        this->valid = other.valid;

        this->x = other.x;
        this->y = other.y;
    }

    // Оператор присвоения копированием
    Dot& operator=(const Dot& other) {

        if (this != &other) {
            this->valid = other.valid;

            this->x = other.x;
            this->y = other.y;
        }

        return *this;
    }

    inline bool operator==(const Dot& other) const {

        if (this->x == other.x && this->y == other.y && this->valid == other.valid) {

            return true;

        }

        return false;

    }

    ~Dot() = default;

};


// Точка на плоскости
struct Point : public Dot {

    // Указатель на цель (кластер) к которой принадлежит данная точка
    Target* target_id = nullptr;

    Point() = default;

    Point(int x, int y) : Dot(x, y, false), target_id(nullptr) {};

    Point(int x, int y, bool valid) : Dot(x, y, valid), target_id(nullptr) {};

    // Конструктор копирования
    Point(const Point& other)  : Dot(other) {
        this->target_id = other.target_id;
    }

    static Dot squeeze(const Point& original) {

        return {original.x, original.y, original.valid};

    }

    // Оператор присвоения копированием
    Point& operator=(const Point& other) {

        if (this != &other) {
            this->target_id = other.target_id;
            this->valid = other.valid;

            this->x = other.x;
            this->y = other.y;
        }

        return *this;
    }

};

#endif //CLUSTERIZATION_POINT_H
