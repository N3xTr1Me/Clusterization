set(CMAKE_CXX_STANDARD 11)

set(TEST_MODULES
        data_structures/point_tests.h
        data_structures/domain_tests.h
        data_structures/target_tests.h
)

add_executable(unit_tests main.cpp ${TEST_MODULES})
