cmake_minimum_required(VERSION 3.25)
project(TSPPartitionHeuristic C)

include(CTest)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

add_subdirectory(test)

#add_executable(TSPPartitionHeuristic src/model/model.c)

enable_testing()
