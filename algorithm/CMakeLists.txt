cmake_minimum_required(VERSION 3.23)
project(algorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(algorithm main.cpp data_structures/target.h data_structures/point.h config.h data_structures/domain.h solver/solution.h solver/solver.cpp solver/solver.h)