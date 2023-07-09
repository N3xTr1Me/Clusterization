#ifndef CLUSTERIZATION_CONFIG_H
#define CLUSTERIZATION_CONFIG_H

#define TARGET_LIMIT 10
#define POINT_LIMIT 20

#define X_LIMIT 11
#define Y_LIMIT 13


struct Config {

    const unsigned int number_of_targets = TARGET_LIMIT;
    const unsigned int points_in_target = POINT_LIMIT;

    const int x_epsilon = 2;
    const int y_epsilon = 2;

    Config() = default;
    Config(int x_epsilon, int y_epsilon) : x_epsilon(x_epsilon), y_epsilon(y_epsilon) {};
    Config(int x_epsilon, int y_epsilon, unsigned int n_targets, unsigned int n_points) :
    x_epsilon(x_epsilon), y_epsilon(y_epsilon), number_of_targets(n_targets), points_in_target(n_points) {};

    ~Config() = default;

};

#endif //CLUSTERIZATION_CONFIG_H
