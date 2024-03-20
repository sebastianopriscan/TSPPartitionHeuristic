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


add_library(TSPPartitionHeuristicSampled STATIC
        src/model/distanceGenFunctions.c
        src/model/reconstructionFunctions.c
        src/model/TSPHeuAlgo.c
        src/model/TSPModel.c
        src/sampler/sampler.c
    )

target_compile_definitions(TSPPartitionHeuristicSampled PRIVATE -DSAMPLER_ENABLED)    


add_library(TSPPartitionHeuristic STATIC
        src/model/distanceGenFunctions.c
        src/model/reconstructionFunctions.c
        src/model/TSPHeuAlgo.c
        src/model/TSPModel.c
    )

enable_testing()
