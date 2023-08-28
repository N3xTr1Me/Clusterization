#ifndef CLUSTERIZATION_TARGET_TESTS_H
#define CLUSTERIZATION_TARGET_TESTS_H

#include <cassert>
#include <iostream>

#include "../../../algorithm/data_structures/target.h"


namespace Target_tests {

    void default_construction() {

        Target test{};

        assert(test.get_size() == 0);

        for (unsigned int i = 0; i < POINT_LIMIT; ++i) {

            assert(test[i].x == 0);
            assert(test[i].y == 0);
            assert(test[i].valid == false);

        }

        std::cout << "Default construction: OK" << std::endl;

    }

    void point_appending() {

        Target test{};

        const int sample_size = 8;

        Point sample[sample_size];

        for (int i = 0; i < sample_size; ++i) {

            sample[i] = Point(i, i, true);
            test.add_point(sample[i]);
            assert(sample[i].target_id == &test);

        }

        std::cout << "Appending points: OK" << std::endl;

    }

    void copy_construction_assignment() {

        Target test{};

        Point data{7, 21, true};
        test.add_point(data);

        Target copy{test};
        assert(copy[0] == test[0]);
        std::cout << "Copy-construction: OK" << std::endl;

        Target assignment = test;
        assert(assignment[0] == test[0]);
        std::cout << "Copy-assignment: OK" << std::endl;

    }

    void run_test() {

        std::cout << "\nTarget data structure testing: \n{" << std::endl;

        default_construction();
        point_appending();
        copy_construction_assignment();

        std::cout << "}\n" << std::endl;
    }

}


#endif //CLUSTERIZATION_TARGET_TESTS_H
