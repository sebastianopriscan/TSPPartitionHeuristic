cmake_minimum_required(VERSION 3.25)
project(TSPPartitionHeuristic C)

set(CMAKE_C_STANDARD 11)

if (BUILD_TESTING)

    add_executable(TestTSPModelCreate testTSPModelCreate.c ../src/model/TSPModel.c)

    add_test(TestTSPModelCreate TestTSPModelCreate)

    add_executable(TestTSPModelCorrectnessChecks testTSPModelCorrectnessChecks.c ../src/model/TSPModel.c)

    add_test(TestTSPModelCorrectnessChecks TestTSPModelCorrectnessChecks)

    add_executable(TestTSPModelConnectionChecks testTSPModelConnectionChecks.c ../src/model/TSPModel.c)

    add_test(TestTSPModelConnectionChecks TestTSPModelConnectionChecks)

    add_executable(TestTSPModelMetaModelChecks testTSPModelMetaModelChecks.c ../src/model/TSPModel.c)

    add_test(TestTSPModelMetaModelChecks TestTSPModelMetaModelChecks)

    add_executable(TestTSPModelCostChecks testTSPModelCostChecks.c ../src/model/TSPModel.c)

    add_test(TestTSPModelCostChecks TestTSPModelCostChecks)

    add_executable(TestTSPModelMaxDistFunction testTSPModelMaxDistFunction.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c)

    add_test(TestTSPModelMaxDistFunction TestTSPModelMaxDistFunction)

    add_executable(TestTSPModelMinDistFunction testTSPModelMinDistFunction.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c)

    add_test(TestTSPModelMinDistFunction TestTSPModelMinDistFunction)

    add_executable(TestTSPModelAvgDistFunction testTSPModelAvgDistFunction.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c)

    add_test(TestTSPModelAvgDistFunction TestTSPModelAvgDistFunction)

endif ()
