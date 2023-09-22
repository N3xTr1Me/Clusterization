#ifndef CLUSTERIZATION_POINT_TESTS_H
#define CLUSTERIZATION_POINT_TESTS_H

#include <cassert>
#include <iostream>

#include "../../../algorithm/data_structures/point.h"


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

    void full_parameter_construction() {

        int x = 10;
        int y = 20;

        Point sample{x, y};

        assert(sample.target_id == nullptr);
        assert(sample.x == x);
        assert(sample.y == y);

        std::cout << "Three-parameter construction: OK" << std::endl;

    }

    void copy_construction_and_assignment() {

        int x = 100;
        int y = 200;

        Point original{x, y};

        //--------------------------------------------------------------------------------------------------------------

        Point constructor{original};

        assert(constructor.target_id == nullptr);
        assert(constructor.x == x);
        assert(constructor.y == y);

        std::cout << "Copy-construction: OK" << std::endl;

        //--------------------------------------------------------------------------------------------------------------

        Point assignment = original;

        assert(assignment.target_id == nullptr);
        assert(assignment.x == x);
        assert(assignment.y == y);

        std::cout << "Copy-assignment: OK" << std::endl;

    }

    void squeeze_to_base() {

        int x = 12;
        int y = 14;

        Point original{x, y};

        auto copy = Point::squeeze(original);

        assert(copy.x == x);
        assert(copy.y == y);

        std::cout << "Copy to base class: OK" << std::endl;

    }

    void run_tests() {

        std::cout << "\nPoint data structure testing: \n{" << std::endl;

        default_construction();
        coordinate_construction();
        full_parameter_construction();
        copy_construction_and_assignment();
        squeeze_to_base();

        std::cout << "}\n" << std::endl;
    }

}


#endif //CLUSTERIZATION_POINT_TESTS_H
