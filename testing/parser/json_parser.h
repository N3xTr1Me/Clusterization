#ifndef CLUSTERIZATION_TEST_JSON_PARSER_H
#define CLUSTERIZATION_TEST_JSON_PARSER_H

#include <string>
#include <iostream>
#include <fstream>

#include "../lib/json/json.h"

#include "../../algorithm/solver/solution.h"


inline Target make_target(const Json::Value& points) {

    Target result{};

    for (auto const& point : points) {
        Point p{point["x_value"].asInt(), point["y_value"].asInt(), true};
        result.add_point(p);
    }

    return result;

}


Solution make_solution(const Json::Value& targets, unsigned int x_size, unsigned int y_size) {
    unsigned int number_of_targets = 0;
    Target data[TARGET_LIMIT];

    std::cout << "size: " << targets.size() << std::endl;

    for (const auto& target : targets) {

        if (number_of_targets > TARGET_LIMIT) {
            break;
        }
        std::cout << number_of_targets << std::endl;
        data[number_of_targets++] = make_target(target);
    }

    return {data, number_of_targets, x_size, y_size};
}


void test(std::string path) {
    std::ifstream input;
    Json::Value data;

    input.open(path, std::ifstream::binary);

    if (input.is_open()) {
        input >> data;
        std::cout << data["targets"] << std::endl;
        input.close();
    }
    else {
        std::cout << "Couldn't open!" << std::endl;
    }

    auto res = make_solution(data["targets"],
                             data["x_axis"]["max_value"].asUInt(),
                             data["y_axis"]["max_value"].asUInt());

    std::cout << "" << std::endl;

}




#endif //CLUSTERIZATION_TEST_JSON_PARSER_H
