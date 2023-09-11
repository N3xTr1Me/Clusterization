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

        // Костыль Для тестирования
        Point* hard_get(unsigned int x, unsigned int y) noexcept {

            if (x >= X_LIMIT) {
                return nullptr;
            }

            if (y >= Y_LIMIT) {
                return nullptr;
            }

            return &this->plane[y][x];
        };

        ~TestDomain() override = default;
    };

    void default_construction() {

        TestDomain sample{};

        assert(sample.get_x_size() == 0);
        assert(sample.get_y_size() == 0);

        std::cout << "Default construction size assertion: OK" << std::endl;

        for (unsigned int y = 0; y < Y_LIMIT; ++y) {
            for(unsigned int x = 0; x < X_LIMIT; ++x) {
                Point* dot = sample.hard_get(x, y);

                if (dot == nullptr) {
                    throw std::runtime_error("Received a null point (nullptr)! "
                                             "This should not happen, as Point struct provides a default constructor.");
                }

                assert(dot->target_id == nullptr);
                assert(dot->valid == false);
                assert(dot->x == 0);
                assert(dot->y == 0);
            }
        }

        std::cout << "Default construction point data assertion: OK" << std::endl;

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

        Domain sample{points};

        for (auto test : cases) {
            Point original = sample[test[1]][test[0]];

            // На всякий случай...
            assert(original.x == test[0]);
            assert(original.y == test[1]);

            assert(original.target_id == nullptr);
            assert(original.valid == true);
        }

        std::cout << "Fixed size construction: OK" << std::endl;

    }

    void _generate_domain(int** data, unsigned int x_size, unsigned int y_size) {

        if (x_size > X_LIMIT) {

            if (State::call().notification_mode()) {
                std::cerr << "[Domain generation] X coordinate out of bounds! "
                             "(replaced with default value)" << std::endl;
            }

            x_size = X_LIMIT;
        }

        if (y_size > Y_LIMIT) {

            if (State::call().notification_mode()) {
                std::cerr << "[Domain generation] Y coordinate out of bounds! "
                             "(replaced with default value)" << std::endl;
            }

            y_size = Y_LIMIT;
        }

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 1);

        for (unsigned int y = 0; y < y_size; ++y) {
            for (unsigned int x = 0; x < x_size; ++x) {
                data[y][x] = distribution(rng);
            }
        }

    }

    void custom_size_construction() {

        int test_case[Y_LIMIT][X_LIMIT];

        int* test[Y_LIMIT];

        for (unsigned int i = 0; i < Y_LIMIT; ++i) {
            test[i] = test_case[i];
        }

        _generate_domain(test, X_LIMIT, Y_LIMIT);

        Domain sample{test, X_LIMIT, Y_LIMIT};

        for (unsigned int y = 0; y < Y_LIMIT; ++y) {
            for (unsigned int x = 0; x < X_LIMIT; ++x) {

                if (test_case[y][x] > 0) {
                    assert(sample[y][x].valid == true);
                }

            }
        }

        std::cout << "Custom size construction: OK" << std::endl;

    }

    void border_errors() {

        unsigned int x_size = X_LIMIT + 1;
        unsigned int y_size = Y_LIMIT + 1;

        int test_case[y_size][x_size];

        int* test[y_size];

        for (unsigned int i = 0; i < y_size; ++i) {
            test[i] = test_case[i];
        }

        _generate_domain(test, x_size, y_size);

        Domain sample{test, x_size, y_size};

        assert(State::call().check(Errors::domain_X_border_breach) == 1);
        assert(State::call().check(Errors::domain_Y_border_breach) == 1);

        std::cout << "X/Y size errors handling: OK" << std::endl;

    }

    void index_error() {

        Domain sample{};

        auto point = sample[1];

        assert(point == nullptr);
        assert(State::call().check(Errors::domain_index_out_of_bounds) == 1);

        std::cout << "Index out of bounds handling: OK" << std::endl;

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
