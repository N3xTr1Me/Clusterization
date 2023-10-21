#ifndef CLUSTERIZATION_TARGET_TESTS_H
#define CLUSTERIZATION_TARGET_TESTS_H

#include <cassert>
#include <iostream>

#include "../../../algorithm/data_structures/target.h"
#include "./point_tests.h"


namespace Target_utility {

    bool equal(const Target& first, const Target& second) {

        if (first.get_size() != second.get_size()) {
            return false;
        }

        for (unsigned int i = 0; i < first.get_size(); ++i) {

            if (!Point_utility::dots_equal(first[i], second[i])) {
                return false;
            }

        }

        return true;

    }

}


namespace Target_tests {

    class TestTarget : public Target {

        public:

        TestTarget() : Target() {};

        TestTarget(const Target& original) : Target(original) {};

        // !!! Метод небезопасен, т.к. его задача выдать нефильтрованные данные из Target::points. 
        // Следует использовать только для тестирования.
        Dot* hard_get(unsigned int index) { return &this->points[index]; }

    };

    //--------------------------------------------------------------------------------------------------------------

    // Служебынй метод для упрощения проверки стандартного конструктора целей
    bool _check_default_target_construction(const Target& sample) {

        if (sample.get_size() > 0) {
            return false;
        }

        TestTarget resource{sample};

        for (unsigned int i = 0; i < POINT_LIMIT; ++i) {

            auto dot = resource.hard_get(i);

            if (dot == nullptr) {
                return false;
            }

            if (dot->x != 0 || dot->y != 0) {
                return false;
            }

        }

        return true;

    }

    //--------------------------------------------------------------------------------------------------------------


    void default_construction() {

        TestTarget test{};

        //----------------------------------------------------------------------------------------------------------

        assert(test.get_size() == 0);
        assert(_check_default_target_construction(test));

        //----------------------------------------------------------------------------------------------------------

        std::cout << "Default construction: OK" << std::endl;

    }

    void point_appending() {

        Target test{};

        int sample_size = 8;

        Point sample[sample_size];

        //----------------------------------------------------------------------------------------------------------

        for (int i = 0; i < sample_size; ++i) {

            sample[i] = Point(i, i);

            test.add_point(sample[i]);

            assert(sample[i].target_id == &test);

        }

        //----------------------------------------------------------------------------------------------------------

        std::cout << "Appending points: OK" << std::endl;

    }

    void copy_construction_assignment() {

        Target original{};
        Point data{7, 21};

        original.add_point(data);

        //----------------------------------------------------------------------------------------------------------

        Target copy{original};

        assert(Point_utility::dots_equal(copy[0], original[0]));

        std::cout << "Copy-construction: OK" << std::endl;

        //----------------------------------------------------------------------------------------------------------

        Target assignment = original;

        assert(Point_utility::dots_equal(assignment[0], original[0]));

        std::cout << "Copy-assignment: OK" << std::endl;

    }

    void point_overflow() {

        // Для чистоты эксперимента обнуляем счетчики ошибок
        State::call().reset();

        Target sample{};

        //----------------------------------------------------------------------------------------------------------

        // забиваем цель точками до переполнения
        for (unsigned int i = 0; i < POINT_LIMIT + 1; ++i) {
            Point p{};
            sample.add_point(p);
        }

        //----------------------------------------------------------------------------------------------------------

        // Проверяем, что цель заполнена
        assert(sample.get_size() == POINT_LIMIT);
        // Проверяем, что сработала обработка ошибки переполнения
        assert(State::call().check(Errors::target_points_overflow) == 1);

        std::cout << "Point overflow handling: OK" << std::endl;

    }

    void run_test() {

        std::cout << "\nTarget data structure testing: \n{" << std::endl;

        default_construction();
        point_appending();
        copy_construction_assignment();
        point_overflow();

        std::cout << "}\n" << std::endl;
    }

}


#endif //CLUSTERIZATION_TARGET_TESTS_H
