cmake_minimum_required(VERSION 3.25)
project(TSPPartitionHeuristic C)

set(CMAKE_C_STANDARD 11)

if (BUILD_TESTING)

    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
    find_package(HIGHS REQUIRED)

    include_directories(${HIGHS_INCLUDE_DIR})

    if(${HIGHS_INCLUDE_DIR} STREQUAL ${HIGHS_SOURCE_DIR}/HiGHS/src)
        set(HIGHS_INCLUDE_BUILD ${HIGHS_INCLUDE_DIR}/../build)
        include_directories(${HIGHS_INCLUDE_BUILD})
    endif (${HIGHS_INCLUDE_DIR} STREQUAL ${HIGHS_SOURCE_DIR}/HiGHS/src)


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

    add_executable(TestTSPModelMetadata testTSPModelMetadata.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c)

    add_test(TestTSPModelMetadata TestTSPModelMetadata)

    add_executable(TestTSPModelMinReconstruction testTSPModelMinReconstruction.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c ../src/model/reconstructionFunctions.c)

    add_test(TestTSPModelMinReconstruction TestTSPModelMinReconstruction)

    add_executable(TestTSPModelMinDistFunctionSaving testTSPModelMinDistFunctionSaving.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c)

    add_test(TestTSPModelMinDistFunctionSaving TestTSPModelMinDistFunctionSaving)

    add_executable(TestTSPModelMaxDistFunctionSaving testTSPModelMaxDistFunctionSaving.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c)

    add_test(TestTSPModelMaxDistFunctionSaving TestTSPModelMaxDistFunctionSaving)

    add_executable(TestTSPModelAvgDistFunctionSaving testTSPModelAvgDistFunctionSaving.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c)

    add_test(TestTSPModelAvgDistFunctionSaving TestTSPModelAvgDistFunctionSaving)

    add_executable(TestTSPModelSavingReconstruction testTSPModelSavingReconstruction.c ../src/model/TSPModel.c ../src/model/distanceGenFunctions.c ../src/model/reconstructionFunctions.c)

    add_test(TestTSPModelSavingReconstruction TestTSPModelSavingReconstruction)
    
    if(TEST_SOLVER_USING_TESTS)
        add_executable(TestSolverIntegration testSolverInclusion.c)

        target_include_directories(TestSolverIntegration PRIVATE ${HIGHS_INCLUDE_DIR})

        target_link_libraries(TestSolverIntegration ${HIGHS_LIBRARIES})

        add_test(TestSolverIntegration TestSolverIntegration)

        add_executable(TestSolver testSolver.c ../src/model/TSPModel.c solvers/highsSolver.c)

        target_include_directories(TestSolver PRIVATE ${HIGHS_INCLUDE_DIR})

        target_link_libraries(TestSolver ${HIGHS_LIBRARIES} m)

        add_test(TestSolver TestSolver)
    endif ()

endif ()
