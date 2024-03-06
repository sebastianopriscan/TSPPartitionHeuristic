cmake_minimum_required(VERSION 3.25)
project(TSPPartitionHeuristic C)

include(CTest)

set(CMAKE_C_STANDARD 11)

if(WIN32)
    add_compile_options(-Wall)
else(WIN32)
    add_compile_options(-Wall -Wextra)
endif(WIN32)

add_subdirectory(test)

add_library(TSPPartitionHeuristic STATIC
        src/model/distanceGenFunctions.c
        src/model/reconstructionFunctions.c
        src/model/TSPHeuAlgo.c
        src/model/TSPModel.c
        )

enable_testing()
