#include "solver.h"

#include <iostream>

bool Solver::is_valid(const Point &point) {
    return point.valid;
}

unsigned int Solver::distance(int original, int adjacent, int epsilon) {

    if (abs(original - adjacent) > epsilon) {
        return 0;
    }

    return abs(original - adjacent);

}

void Solver::add_target(Point &first_point) {
    if (this->number_of_targets < TARGET_LIMIT) {
        this->targets[this->number_of_targets++] = Target(first_point);
    }
}

void Solver::pick_cluster(Domain &domain, unsigned int x, unsigned int y, int x_epsilon, int y_epsilon) {

    const Point& original = domain[y][x];

    unsigned int B = x_epsilon + 1;
    unsigned int C = y_epsilon + 1;

    ITarget* X_neighbour = nullptr;
    ITarget* Y_neighbour = nullptr;

    for (int j = original.x - x_epsilon; j < original.x; ++j) {

        if (j < 0) {
            continue;
        }

        if (this->is_valid(domain[y][j])) {

            unsigned int distance = this->distance(original.x, domain[y][j].x, x_epsilon);

            if (distance != 0 && distance < B && domain[y][j].target_id != nullptr) {
                B = distance;
                X_neighbour = domain[y][j].target_id;
            }
        }
    }

    for (int i = original.y - y_epsilon; i < original.y; ++i) {

        if (i < 0) {
            continue;
        }

        if (this->is_valid(domain[i][x])) {

            unsigned int distance = this->distance(original.y, domain[i][x].y, y_epsilon);

            if (distance != 0 && distance < C && domain[i][x].target_id != nullptr) {
                C = distance;
                Y_neighbour = domain[i][x].target_id;
            }
        }
    }

    if (B == x_epsilon + 1 && C != y_epsilon + 1 && Y_neighbour != nullptr) {
        Y_neighbour->add_point(domain[y][x]);
        return;
    }

    if (B != x_epsilon + 1 && C == y_epsilon + 1 && X_neighbour != nullptr) {
        X_neighbour->add_point(domain[y][x]);
        return;
    }

    if ((B == x_epsilon + 1 && C == y_epsilon + 1) || (X_neighbour == nullptr && Y_neighbour == nullptr)) {
        this->add_target(domain[y][x]);
        return;
    }

    if (B != x_epsilon + 1 && C != y_epsilon + 1 && X_neighbour != nullptr && Y_neighbour != nullptr) {

        if (B == C) {
            X_neighbour->add_point(domain[y][x]);
            return;
        }
        else {
            Y_neighbour->add_point(domain[y][x]);
            return;
        }
    }

}

Solution Solver::clusterize(Domain &domain, Config config) {

    this->number_of_targets = 0;

    for (unsigned int y = 0; y < domain.get_y_size(); ++y) {
        for (unsigned int x = 0; x < domain.get_x_size(); ++x) {

            if (this->is_valid(domain[y][x])) {
                this->pick_cluster(domain, x, y,  config.x_epsilon, config.y_epsilon);
            }

        }
    }

    return {this->targets, this->number_of_targets};

}
