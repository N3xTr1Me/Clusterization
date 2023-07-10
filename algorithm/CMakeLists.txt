cmake_minimum_required(VERSION 3.23)
project(clusterization)

set(CMAKE_CXX_STANDARD 11)

add_executable(clusterization main.cpp data_structures/target.h data_structures/point.h config.h data_structures/domain.h solver/solution.h solver/solver.cpp solver/solver.h)