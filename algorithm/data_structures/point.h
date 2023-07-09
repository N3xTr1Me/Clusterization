#ifndef CLUSTERIZATION_POINT_H
#define CLUSTERIZATION_POINT_H

#include "../config.h"

class ITarget;


struct Point {

    ITarget* target_id = nullptr;
    bool valid = false;

    int x = 0;
    int y = 0;

    Point() = default;
    Point(int x, int y) : x(x), y(y), valid(false), target_id(nullptr) {};
    Point(int x, int y, bool valid) : x(x), y(y), valid(valid), target_id(nullptr) {};

    ~Point() = default;

};

#endif //CLUSTERIZATION_POINT_H
