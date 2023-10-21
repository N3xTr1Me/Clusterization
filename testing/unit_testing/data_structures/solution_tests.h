#ifndef CLUSTERIZATION_SOLUTION_TESTS_H
#define CLUSTERIZATION_SOLUTION_TESTS_H

#include <cassert>
#include <iostream>

#include "../../../algorithm/data_structures/solution.h"
#include "./target_tests.h"


namespace Solution_tests {


    void default_construction() {

        Solution sample{};

        assert(sample.get_size() == 0);

        for (unsigned int i = 0; i < TARGET_LIMIT; ++i) {

            for (unsigned int j = 0; j < POINT_LIMIT; ++ j) {

                assert(Target_tests::_check_default_target_construction(sample[i]));

            }

        }

        std::cout << "Default construction: OK" << std::endl;

    }

    void two_parameter_construction() {

        unsigned int number_of_targets = TARGET_LIMIT / 2;
        Target test_targets[TARGET_LIMIT];

        //----------------------------------------------------------------------------------------------------------

        for (unsigned int i = 0; i < number_of_targets; ++i) {

            test_targets[i] = Target(Dot(i, i));

        }

        Solution sample{test_targets, number_of_targets};

        //----------------------------------------------------------------------------------------------------------

        assert(sample.get_size() == number_of_targets);
        
        for (unsigned int i = 0; i < sample.get_size(); ++i) {

            assert(Target_utility::equal(sample[i], test_targets[i]));

        }

        std::cout << "Two-parameter construction: OK" << std::endl;

    }

    void copy_construction_assignment() {

        Target test_targets[TARGET_LIMIT];

        for (unsigned int i = 0; i < TARGET_LIMIT; ++i) {

            test_targets[i] = Target(Dot(i, i));

        }

        Solution original{test_targets, TARGET_LIMIT};

        //----------------------------------------------------------------------------------------------------------

        Solution copy{original};

        assert(copy.get_size() == original.get_size());

        for (unsigned int i = 0; i < copy.get_size(); ++i) {

            assert(Target_utility::equal(copy[i], original[i]));

        }

        std::cout << "Copy construction: OK" << std::endl;

        //----------------------------------------------------------------------------------------------------------

        Solution assignment = original;

        assert(assignment.get_size() == original.get_size());

        for (unsigned int i = 0; i < assignment.get_size(); ++i) {

            assert(Target_utility::equal(assignment[i], original[i]));

        }

        std::cout << "Copy-assignment: OK" << std::endl;

    }

    void size_limit_excess() {

        // Обнуляем счетчики ошибок
        State::call().reset();

        //----------------------------------------------------------------------------------------------------------

        Target test_targets[TARGET_LIMIT];

        for (unsigned int i = 0; i < TARGET_LIMIT; ++i) {

            test_targets[i] = Target(Dot(i, i));

        }

        Solution sample{test_targets, TARGET_LIMIT + 1};

        //----------------------------------------------------------------------------------------------------------

        assert(sample.get_size() == TARGET_LIMIT);
        assert(State::call().check(Errors::solution_size_limit_exceeded) == 1);

        std::cout << "Size limit excess error handling: OK" << std::endl;

    }

    void run_tests() {

        std::cout << "\nSolution data structure: \n{\n";

        default_construction();
        two_parameter_construction();
        copy_construction_assignment();
        size_limit_excess();

        std::cout << "}\n" << std::endl;

    }

}

#endif //CLUSTERIZATION_SOLUTION_TESTS_H