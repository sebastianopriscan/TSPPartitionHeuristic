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

    if(TEST_SOLVER_USING_TESTS)

        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
        find_package(HIGHS REQUIRED)

        include_directories(${HIGHS_INCLUDE_DIR})

        if(${HIGHS_INCLUDE_DIR} STREQUAL ${HIGHS_SOURCE_DIR}/HiGHS/src)
            set(HIGHS_INCLUDE_BUILD ${HIGHS_INCLUDE_DIR}/../build)
            include_directories(${HIGHS_INCLUDE_BUILD})
        endif (${HIGHS_INCLUDE_DIR} STREQUAL ${HIGHS_SOURCE_DIR}/HiGHS/src)

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
