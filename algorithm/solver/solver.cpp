#include "solver.h"

#include <iostream>

bool Solver::is_valid(const Point &point) {
    // Пока что просто возвращает значение поля точки. В последствии возможно менее тривиальная проверка.
    return point.valid;
}

unsigned int Solver::distance(int original, int adjacent, int epsilon) {

    // Сразу проверяем, что расстояние между точками не больше допустимого epsilon, в противном случае возвращаем 0
    if (abs(original - adjacent) > epsilon) {
        return 0;
    }

    // Расстояние просто модуль разности
    return abs(original - adjacent);

}

void Solver::add_target(Point &first_point) {
    // Проверяем, что целей не больше максимального допустимого количества
    if (this->number_of_targets < TARGET_LIMIT) {
        this->targets[this->number_of_targets++] = Target(first_point);
    }
}

void Solver::pick_cluster(Domain &domain, unsigned int x, unsigned int y, int x_epsilon, int y_epsilon) {

    // Сохраняем константную ссылку для внутренней логики
    const Point& original = domain[y][x];

    // Расстояния по осям X (B) и Y (C)
    unsigned int B = x_epsilon + 1;
    unsigned int C = y_epsilon + 1;

    // Указатели на цели, к которым принадлежат ближайшие соседи исходной точки.
    ITarget* X_neighbour = nullptr;
    ITarget* Y_neighbour = nullptr;

    // Проходимся в строку "влево" по оси X от исходной точки
    for (int j = original.x - x_epsilon; j < original.x; ++j) {

        // Если индекс отрицательный, то мы вышли за границу массива
        if (j < 0) {
            continue;
        }

        if (this->is_valid(domain[y][j])) {

            unsigned int distance = this->distance(original.x, domain[y][j].x, x_epsilon);

            // Проверяем, что расстояние не 0 (т.е. не превышает x_epsilon), оно меньше текущего
            // и что сосед принадлежит к какой либо цели
            if (distance != 0 && distance < B && domain[y][j].target_id != nullptr) {
                B = distance;
                X_neighbour = domain[y][j].target_id;
            }
        }
    }

    // Для Y аналогично, но столбиком "вниз"
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

    // Если мы нашли соседа по оси Y, то добавим исходную в его цель
    if (B == x_epsilon + 1 && C != y_epsilon + 1 && Y_neighbour != nullptr) {
        Y_neighbour->add_point(domain[y][x]);
        return;
    }

    // Тоже, но для соседа по X
    if (B != x_epsilon + 1 && C == y_epsilon + 1 && X_neighbour != nullptr) {
        X_neighbour->add_point(domain[y][x]);
        return;
    }

    // Если соседей нет, то создаем новую цель
    if ((B == x_epsilon + 1 && C == y_epsilon + 1) || (X_neighbour == nullptr && Y_neighbour == nullptr)) {
        this->add_target(domain[y][x]);
        return;
    }

    // Если есть сосед и по X и по Y, то смотрим на расстояние до исходной точки
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
