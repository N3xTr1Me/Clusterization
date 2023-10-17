#ifndef CLUSTERIZATION_POINT_TESTS_H
#define CLUSTERIZATION_POINT_TESTS_H

#include <cassert>
#include <iostream>

#include "../../../algorithm/data_structures/point.h"


namespace Point_tests {

    // Отношения равенства вынесены сюда для удобства тестирования, в исходных классах Dot и Point оператор '==' не определен в угоду оптимизации.

    bool _dots_equal(Dot& first, Dot& second) {

        if (first.x == second.x && first.y == second.y) {
            return true;
        }

        return false;

    }

    bool _points_equal(Point& first, Point& second) {

        if (first.target_id == second.target_id && _dots_equal(first, second)) {
            return true;
        }

        return false;

    }

    //--------------------------------------------------------------------------------------------------------------


    void default_construction() {

        Point sample{};

        assert(sample.target_id == nullptr);
        assert(sample.x == 0);
        assert(sample.y == 0);

        std::cout << "Default construction: OK" << std::endl;

    }

    void coordinate_construction() {

        int x = 12;
        int y = 100;

        Point sample{x, y};

        assert(sample.target_id == nullptr);
        assert(sample.x == x);
        assert(sample.y == y);

        std::cout << "Two-parameter construction: OK" << std::endl;

    }

    void copy_construction_and_assignment() {

        int x = 100;
        int y = 200;

        Point original{x, y};

        //--------------------------------------------------------------------------------------------------------------

        Point constructor{original};

        assert(_points_equal(constructor, original));

        std::cout << "Copy-construction: OK" << std::endl;

        //--------------------------------------------------------------------------------------------------------------

        Point assignment = original;

        assert(_points_equal(assignment, original));

        std::cout << "Copy-assignment: OK" << std::endl;

    }

    void squeeze_to_base() {

        int x = 12;
        int y = 14;

        Point original{x, y};

        auto copy = Point::squeeze(original);

        assert(_dots_equal(copy, original));

        std::cout << "Copy to base class: OK" << std::endl;

    }

    void run_tests() {

        std::cout << "\nPoint data structure testing: \n{" << std::endl;

        default_construction();
        coordinate_construction();
        copy_construction_and_assignment();
        squeeze_to_base();

        std::cout << "}\n" << std::endl;
    }

}


#endif //CLUSTERIZATION_POINT_TESTS_H
