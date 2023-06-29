#ifndef CLASTERIZATION_CONFIG_H
#define CLASTERIZATION_CONFIG_H


struct Config {
    unsigned int limit_of_points = 500;

    int x_epsilon = 1;
    int y_epsilon = 1;
};

#endif //CLASTERIZATION_CONFIG_H
