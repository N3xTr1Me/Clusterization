#ifndef CLUSTERIZATION_TARGET_H
#define CLUSTERIZATION_TARGET_H

#include "./Domain.h"


// Цель, т.е. кластер точек, находящихся рядом друг с другои на плоскости (Близость определяется как расстояния не более
// x_epsilon по оси X и y_espilon по оси Y).
class Target {

protected:

    // "Реальный" размер цели, т.е. количество входящих в нее точек
    unsigned int size = 0;

    Dot points[POINT_LIMIT];

public:

    Target() = default;

    // "Основной" конструктор, создающий цель по первой точке
    explicit Target(const Dot& first) : size(0), points() {

        this->points[this->size++] = first;

    }

    // Конструктор копирования
    Target(const Target& other) {

        this->size = other.size;

        for (unsigned int i = 0; i < this->size; ++i) {
            this->points[i] = other.points[i];
        }

    }

    //------------------------------------------------------------------------------------------------------------------

    inline unsigned int get_size() const noexcept { return this->size; };

    // Добавление точки
    inline void add_point(Point& point) {
        
        // Проверяем на переполнение цели
        if (this->size >= POINT_LIMIT) {
            
            // Если в текущую цель добавить точку нельзя, то сообщим в State
            State::call().report(
                Errors::target_points_overflow,
                "Target is full! Cannot add more points."
            );

            // и ничего не добавим
            return;
        }

        // Если же массив внутри текущей цели не заполнен, то добавим в него упрощенное представление точки 'Dot'
        this->points[this->size++] = Point::squeeze(point);
        // Также заменим в оригинальной указатель на цель, чтобы он указывал на текущую цель
        point.target_id = this;

    }

    //------------------------------------------------------------------------------------------------------------------

    inline const Dot& operator[](unsigned int index) const { return this->points[index]; }

    // Оператор присваивания, логика аналогичная конструктору копирования
    Target& operator=(const Target& other) {

        // Однако еще проверяем на самоприсвоение
        if (this != &other) {

            this->size = other.size;

            for (unsigned int i = 0; i < this->size; ++i) {
                this->points[i] = other.points[i];
            }

        }

        return *this;

    }

    ~Target() = default;
    
};


#endif //CLUSTERIZATION_TARGET_H
