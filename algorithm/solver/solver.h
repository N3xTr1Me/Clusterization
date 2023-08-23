#ifndef CLUSTERIZATION_SOLVER_H
#define CLUSTERIZATION_SOLVER_H

#include "../data_structures/domain.h"
#include "./solution.h"

#include <stdlib.h>


// Обработчик, выполняющий кластеризацию точек
class Solver {

    // Solver работает как state-машина, сохраняя во время работы (выполнения функции clusterize) выделенные цели.
    unsigned int number_of_targets = 0;
    Target targets[TARGET_LIMIT];

protected:

    // Проверка точки на валидность
    inline bool is_valid(const Point& point);

    // Вычисление расстояния по одной из координат между двумя точками
    inline unsigned int distance(int original, int adjacent, int epsilon);

    // Создание новой цели и добавление ее во внутреннее хранилище
    void add_target(Domain &domain, int x, int y);

    void remove_target(ITarget* id);

    // Слияние целей
    void merge(ITarget* original, ITarget* other);

    // Выбор цели конкретной точки
    void pick_cluster(Domain& domain, unsigned int x, unsigned int y, int x_epsilon, int y_epsilon);

public:

    Solver() = default;

    // Клатеризация плоскости
    Solution clusterize(Domain& domain, Config config);

    ~Solver() = default;

};


#endif //CLUSTERIZATION_SOLVER_H
