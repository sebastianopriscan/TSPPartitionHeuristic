cmake_minimum_required(VERSION 3.25)
project(TSPPartitionHeuristic C)

include(CTest)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

add_subdirectory(test)

add_library(TSPPartitionHeuristic STATIC
        src/model/distanceGenFunctions.c
        src/model/reconstructionFunctions.c
        src/model/TSPHeuAlgo.c
        src/model/TSPModel.c
        )

enable_testing()
