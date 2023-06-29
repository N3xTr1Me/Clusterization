#ifndef CLASTERIZATION_POINT_H
#define CLASTERIZATION_POINT_H

struct Point {
    unsigned int target_id = 0;

    int x = 0;
    int y = 0;

    Point() = default;
    Point(int x, int y, unsigned int id) : x(x), y(y), target_id(id) {};
    ~Point() = default;
};

#endif //CLASTERIZATION_POINT_H
