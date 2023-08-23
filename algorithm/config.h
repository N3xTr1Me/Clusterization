#ifndef CLUSTERIZATION_CONFIG_H
#define CLUSTERIZATION_CONFIG_H

#define TARGET_LIMIT 10
#define NEIGHBOUR_LIMIT 8
#define POINT_LIMIT 20

#define X_LIMIT 11
#define Y_LIMIT 13


// Абстракция, чтобы не передавать большое число аргументов.
struct Config {

    // Максимальное количество целей
    const unsigned int number_of_targets = TARGET_LIMIT;
    // Максимальное количество точек в цели
    const unsigned int points_in_target = POINT_LIMIT;

    // Максимальные отступы по осям
    const int x_epsilon = 2;
    const int y_epsilon = 2;

    Config() = default;
    Config(int x_epsilon, int y_epsilon) : x_epsilon(x_epsilon), y_epsilon(y_epsilon) {};
    Config(int x_epsilon, int y_epsilon, unsigned int n_targets, unsigned int n_points) :
    x_epsilon(x_epsilon), y_epsilon(y_epsilon), number_of_targets(n_targets), points_in_target(n_points) {};

    ~Config() = default;

};

#endif //CLUSTERIZATION_CONFIG_H
