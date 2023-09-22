set(CMAKE_CXX_STANDARD 11)

set(ALGORITHM_HDR
        configuration/config.h
        data_structures/point.h
        data_structures/domain.h
        data_structures/target.h
        configuration/state_handler.h
        data_structures/solution.h
)

set(ALGORITHM_SRC
        main.cpp
)

add_executable(algorithm ${ALGORITHM_HDR} ${ALGORITHM_SRC})
