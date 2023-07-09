#ifndef CLUSTERIZATION_POINT_H
#define CLUSTERIZATION_POINT_H

#include "../config.h"

class ITarget;


// Точка на плоскости
struct Point {

    // Указатель на цель (кластер) к которой принадлежит данная точка
    ITarget* target_id = nullptr;
    // Флаг, определяющий будет ли данная точка рассмотрена алгоритмом (т.е. есть ли в ней что-либо)
    bool valid = false;

    // Координаты на плоскости
    int x = 0;
    int y = 0;

    Point() = default;
    Point(int x, int y) : x(x), y(y), valid(false), target_id(nullptr) {};
    Point(int x, int y, bool valid) : x(x), y(y), valid(valid), target_id(nullptr) {};

    ~Point() = default;

};

#endif //CLUSTERIZATION_POINT_H
