set(CMAKE_CXX_STANDARD 20)

set(ALGORITHM_HDR
        config.h
        data_structures/point.h
        data_structures/domain.h
)

set(ALGORITHM_SRC
        main.cpp
)

add_executable(algorithm ${ALGORITHM_HDR} ${ALGORITHM_SRC})
