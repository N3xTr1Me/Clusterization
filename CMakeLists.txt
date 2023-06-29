cmake_minimum_required(VERSION 3.23)
project(clasterization)

set(CMAKE_CXX_STANDARD 20)

add_executable(clasterization main.cpp dataclasses/point.h dataclasses/domain.h dataclasses/domain.cpp dataclasses/config.h io/file_handler.h solver/solver.h)