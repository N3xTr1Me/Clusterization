#ifndef CLUSTERIZATION_DOMAIN_TESTS_H
#define CLUSTERIZATION_DOMAIN_TESTS_H

#define TEST_CASES 7
#define X_LIMIT 20
#define Y_LIMIT 10

#include <cassert>
#include <iostream>
#include <random>

#include "../../../algorithm/data_structures/domain.h"


namespace Domain_tests {


    class TestDomain : public Domain {

        public:

        TestDomain() : Domain() {};
        TestDomain(int points[Y_LIMIT][X_LIMIT]) : Domain(points) {}

        // !!! Метод небезопасен, т.к. его задача выдать нефильтрованные данные из Domain::plane. 
        // Следует использовать только для тестирования.
        Point* hard_get(int x, int y) { return this->plane[y][x]; }

        unsigned int points_in_domain() const { return this->number_of_points; }

    };

    //--------------------------------------------------------------------------------------------------------------

    // Служебынй метод для генерации случайного массива данных для Domain
    void _generate_domain(int** data, unsigned int x_size, unsigned int y_size) {

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 1);

        for (unsigned int y = 0; y < y_size; ++y) {
            for (unsigned int x = 0; x < x_size; ++x) {
                data[y][x] = distribution(rng);
            }
        }

    }

    //--------------------------------------------------------------------------------------------------------------

    void default_construction() {

        TestDomain sample{};

        assert(sample.get_x_size() == X_LIMIT);
        assert(sample.get_y_size() == Y_LIMIT);

        std::cout << "Default construction (size assertion): OK" << std::endl;

        assert(sample.points_in_domain() == 0);

        for (int y = 0; y < Y_LIMIT; ++y) {
            for(int x = 0; x < X_LIMIT; ++x) {

                Point* dot = sample.hard_get(x, y);
                assert(dot == nullptr);

            }
        }

        std::cout << "Default construction (point data assertion): OK" << std::endl;

    }

    void fixed_size_construction() {

        int points[Y_LIMIT][X_LIMIT] = {0};

        int cases[TEST_CASES][2] = {
                {11, 2},
                {0, 0},
                {17, 9},
                {9, 9},
                {19, 8},
                {19, 0},
                {0, 9}
        };

        for (auto test : cases) {
            points[test[1]][test[0]] = 1;
        }

        //----------------------------------------------------------------------------------------------------------

        TestDomain sample{points};

        // Проверим, что записались все точки
        assert(sample.points_in_domain() == TEST_CASES);

        // Проверим каждую отдельно
        for (auto test : cases) {

            int x = test[0];
            int y = test[1];

            Point* original = sample.get_point(x, y);

            // На всякий случай проверим, что точка существует...
            assert(original != nullptr);

            // Проверка точки
            assert(original->x == test[0]);
            assert(original->y == test[1]);

            assert(original->target_id == nullptr);
        }

        std::cout << "Fixed size construction: OK" << std::endl;

    }

    void custom_size_construction() {

        // Опять обнуляем счетчики ошибок для чистоты эксперимента
        State::call().reset();

        //----------------------------------------------------------------------------------------------------------

        unsigned int new_x_size = X_LIMIT + 2;
        unsigned int new_y_size = Y_LIMIT + 1;

        // Создание массива данных с размерами отличными от стандартных
        int test_case[new_y_size][new_x_size];
        int* test[new_y_size];

        // Колхозный каст к int**
        for (unsigned int i = 0; i < new_y_size; ++i) {
            test[i] = test_case[i];
        }

        _generate_domain(test, new_x_size, new_y_size);

        //----------------------------------------------------------------------------------------------------------

        Domain sample{test, new_x_size, new_y_size};

        assert(State::call().check(Errors::domain_X_border_breach) == 1);
        assert(State::call().check(Errors::domain_Y_border_breach) == 1);

        std::cout << "Custom size construction (size limit excess handling): OK " << std::endl;

        //----------------------------------------------------------------------------------------------------------

        for (int y = 0; y < Y_LIMIT; ++y) {
            for (int x = 0; x < X_LIMIT; ++x) {

                if (test_case[y][x] > 0) {
                    
                    // Проверим, что все точки из тестовых записались в Domain
                    auto dot = sample.get_point(x, y);

                    //Проверим, что точка вообще существует в Domain
                    assert(dot != nullptr);

                    // Проверим, что в ней корректные данные
                    assert(dot->target_id == nullptr);
                    assert(dot->x == x);
                    assert(dot->y == y);

                }

            }
        }

        std::cout << "Custom size construction (Point data assertion): OK" << std::endl;

    }

    void border_errors() {

        // Для чистоты эксперимента обнуляем счетчики ошибок
        State::call().reset();

        //----------------------------------------------------------------------------------------------------------

        // Генерация массива бОльших размеров, чем стандартные
        unsigned int x_size = X_LIMIT + 1;
        unsigned int y_size = Y_LIMIT + 1;

        int test_case[y_size][x_size];
        int* test[y_size];

        for (unsigned int i = 0; i < y_size; ++i) {
            test[i] = test_case[i];
        }

        _generate_domain(test, x_size, y_size);

        //----------------------------------------------------------------------------------------------------------

        Domain sample{test, x_size, y_size};

        assert(State::call().check(Errors::domain_X_border_breach) == 1);
        assert(State::call().check(Errors::domain_Y_border_breach) == 1);

        std::cout << "X/Y size errors handling: OK" << std::endl;

    }

    void index_error() {

        // Для чистоты эксперимента обнуляем счетчики ошибок
        State::call().reset();

        Domain sample{};

        int x_error_size = X_LIMIT + 1;
        int y_error_size = Y_LIMIT + 1;

        //----------------------------------------------------------------------------------------------------------

        auto x_error = sample.get_point(x_error_size, 0);
        assert(x_error == nullptr);
        assert(State::call().check(Errors::domain_X_out_of_bounds) == 1);

        std::cout << "X index out of bounds handling: OK" << std::endl;

        //----------------------------------------------------------------------------------------------------------

        auto y_error = sample.get_point(0, y_error_size);
        assert(y_error == nullptr);
        assert(State::call().check(Errors::domain_Y_out_of_bounds) == 1);

        std::cout << "Y index out of bounds handling: OK" << std::endl;

    }

    void run_tests() {

        std::cout << "\nDomain data structure testing: \n{" << std::endl;

        default_construction();
        fixed_size_construction();
        custom_size_construction();
        border_errors();
        index_error();

        std::cout << "}\n" << std::endl;

    }

}


#endif //CLUSTERIZATION_DOMAIN_TESTS_H
