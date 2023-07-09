#ifndef CLUSTERIZATION_SOLVER_H
#define CLUSTERIZATION_SOLVER_H

#include "../data_structures/domain.h"
#include "./solution.h"

#include <stdlib.h>


class Solver {

    unsigned int number_of_targets = 0;
    Target targets[TARGET_LIMIT];

protected:

    inline bool is_valid(const Point& point);

    inline unsigned int distance(int original, int adjacent, int epsilon);

    void add_target(Point& first_point);

    void pick_cluster(Domain& domain, unsigned int x, unsigned int y, int x_epsilon, int y_epsilon);

public:

    Solver() = default;

    Solution clusterize(Domain& domain, Config config);

    ~Solver() = default;

};


#endif //CLUSTERIZATION_SOLVER_H
