#ifndef CLUSTERIZATION_CONFIG_H
#define CLUSTERIZATION_CONFIG_H

#define X_LIMIT 4000        // Максимальное значение по оси X
#define Y_LIMIT 36          // Максимальное значение по оси Y

#define X_SHIFT 2           // Максимальный отступ между точками ОДНОЙ цели по оси X
#define Y_SHIFT 2           // Аналогично для оси Y

#define TARGET_LIMIT 10     // Максимумальное число целей, на которое алгоритм разобьет точки на плоскости
#define POINT_LIMIT 15      // Максимум точек в отдельной цели


struct AlgorithmConfig {

    const int x_epsilon = X_SHIFT;
    const int y_epsilon = Y_SHIFT;

    const unsigned int targets_max = TARGET_LIMIT;
    const unsigned int points_max = POINT_LIMIT;

    AlgorithmConfig() = default;

    //------------------------------------------------------------------------------------------------------------------
    // Конструкторы кастомизируемых конфигураций
    AlgorithmConfig(int x_shift, int y_shift) :
    x_epsilon(x_shift), y_epsilon(y_shift), targets_max(TARGET_LIMIT), points_max(POINT_LIMIT) {};

    AlgorithmConfig(unsigned int max_targets, unsigned int max_points) :
    x_epsilon(X_SHIFT), y_epsilon(Y_SHIFT), targets_max(max_targets), points_max(max_points) {};

    AlgorithmConfig(int x_shift, int y_shift, unsigned int max_targets, unsigned int max_points) :
    x_epsilon(x_shift), y_epsilon(y_shift), targets_max(max_targets), points_max(max_points) {};

    //------------------------------------------------------------------------------------------------------------------

    ~AlgorithmConfig() = default;

};


#endif //CLUSTERIZATION_CONFIG_H
