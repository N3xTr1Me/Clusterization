cmake_minimum_required(VERSION 3.23)
project(clusterization_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(clusterization_test lib/json/json-forwards.h lib/json/json.h lib/json/jsoncpp.cpp main.cpp parser/json_parser.h)