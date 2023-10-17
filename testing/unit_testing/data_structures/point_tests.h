#ifndef CLUSTERIZATION_POINT_TESTS_H
#define CLUSTERIZATION_POINT_TESTS_H

#include <cassert>
#include <iostream>

#include "../../../algorithm/data_structures/point.h"


namespace Point_utility {

    // Отношения равенства вынесены сюда для удобства тестирования. 
    // В исходных классах Dot и Point оператор '==' не определен в угоду оптимизации.

    inline bool dots_equal(const Dot& first, const Dot& second) {

        if (first.x == second.x && first.y == second.y) {
            return true;
        }

        return false;

    }

    inline bool points_equal(const Point& first, const Point& second) {

        if (first.target_id == second.target_id && dots_equal(first, second)) {
            return true;
        }

        return false;

    }

}


namespace Point_tests {

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

        assert(Point_utility::points_equal(constructor, original));

        std::cout << "Copy-construction: OK" << std::endl;

        //--------------------------------------------------------------------------------------------------------------

        Point assignment = original;

        assert(Point_utility::points_equal(assignment, original));

        std::cout << "Copy-assignment: OK" << std::endl;

    }

    void squeeze_to_base() {

        int x = 12;
        int y = 14;

        Point original{x, y};

        auto copy = Point::squeeze(original);

        assert(Point_utility::dots_equal(copy, original));

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
