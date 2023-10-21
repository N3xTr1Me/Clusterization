#ifndef CLUSTERIZATION_STATE_HANDLER_H
#define CLUSTERIZATION_STATE_HANDLER_H

#include <iostream>
#include <string>

#include "./config.h"


enum Errors : unsigned int
{
    
    domain_X_border_breach,
    domain_Y_border_breach,
    domain_X_out_of_bounds,
    domain_Y_out_of_bounds,

    target_points_overflow,

    solution_size_limit_exceeded,

    //------------------------------------------------------------------------------------------------------------------
    // Количество 'кодов' ошибок. Нужно для создания массива в State.
    // !!!Всегда должно находиться в конце энумерации!!!

    error_codes

};


class Solver;


// Синглтон Майерса
class State {

    State() = default;
    ~State() = default;

    // Вместо проверки индекса просто выделим еще памяти на случай обращения по индексу "Errors::error_codes"
    unsigned int errors[Errors::error_codes + 1] = {0};

protected:

    // Флаг для режима сообщения об ошибках пользователю
    bool notify = false;

    // Флаги для разрешения некритических ошибок
    bool current_target_full = false;

public:

    static State& call() {
        static State instance;
        return instance;
    }

    // Объявляем класс алгоритма другом, для доступа к приватным флагам State с целью оптимизации.
    friend Solver;

    //------------------------------------------------------------------------------------------------------------------
    // Конфигурация алгоритма

    static const int x_epsilon = X_LIMIT;
    static const int y_epsilon = Y_LIMIT;

    static const unsigned int points_max = POINT_LIMIT;
    static const unsigned int targets_max = TARGET_LIMIT;

    //------------------------------------------------------------------------------------------------------------------

    // Метод индикации ошибок
    void report(Errors code, std::string message = "") noexcept {

        // Записываем ошибку в соответсвующую позицию массива ошибок
        this->errors[code]++;

        // В случае, если текущая цель переполнина меняем флаг, чтобы передать эту информацию Solver
        if (code == Errors::target_points_overflow) {
            this->current_target_full = true;
        }

        // Проверяем не выключеы ли уведомления и есть ли что выводить вообще
        if (this->notify && message.size() > 0) {
            //Выводим сообщение об ошибке в отдельный поток
            std::cerr << message << "\n";
        }

    }

    // Метод сброса счетчиков ошибок
    void reset() noexcept {

        for (unsigned int i = 0; i < Errors::error_codes; ++i) {
            this->errors[i] = 0;
        }

    }

    //------------------------------------------------------------------------------------------------------------------
    // Методы-геттеры

    unsigned int check(Errors code) const noexcept { return this->errors[code]; }

    bool notifications_on() const noexcept { return this->notify; }

    //------------------------------------------------------------------------------------------------------------------
    // Смена режима оповещения об ошибках

    void enable_notification() noexcept { this->notify = true; }
    void disable_notification() noexcept { this->notify = false; }

};


#endif //CLUSTERIZATION_STATE_HANDLER_H
