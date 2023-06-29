#ifndef CLASTERIZATION_SOLVER_H
#define CLASTERIZATION_SOLVER_H

#include "../dataclasses/domain.h"


class Solver {
    int x_epsilon;
    int y_epsilon;

protected:

    unsigned int neighbours_id(Domain& domain, unsigned int x, unsigned int y);
    bool check_point(const Point&);

public:

    Solver(int x_epsilon, int y_epsilon);

    void clasterize(Domain& domain);

    ~Solver() = default;

};


#endif //CLASTERIZATION_SOLVER_H
