#ifndef CLUSTERIZATION_STATE_HANDLER_H
#define CLUSTERIZATION_STATE_HANDLER_H

#include "./config.h"


enum Errors : unsigned int
{
    
    domain_X_border_breach,
    domain_Y_border_breach,
    domain_X_out_of_bounds,
    domain_Y_out_of_bounds,

    target_points_overflow,
    target_index_out_of_bounds,

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
    bool mute = false;

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
    void report(Errors code) noexcept {

        // Записываем ошибку в соответсвующую позицию массива ошибок
        this->errors[code]++;

        // В случае, если текущая цель переполнина меняем флаг, чтобы передать эту информацию Solver
        if (code == Errors::target_points_overflow) {
            this->current_target_full = true;
        }

    }

    // Метод сброса счетчиков ошибок
    void reset() {

        for (unsigned int i = 0; i < Errors::error_codes; ++i) {
            this->errors[i] = 0;
        }

    }

    //------------------------------------------------------------------------------------------------------------------
    // Методы-геттеры

    unsigned int check(Errors code) const noexcept { return this->errors[code]; }

    bool notification_mode() const noexcept { return this->mute; }

    //------------------------------------------------------------------------------------------------------------------
    // Смена режима оповещения об ошибках

    void enable_notification() { this->mute = true; }
    void disable_notification() { this->mute = false; }

};


#endif //CLUSTERIZATION_STATE_HANDLER_H
