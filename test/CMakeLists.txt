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

        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
        find_package(HIGHS REQUIRED)

        include_directories(${HIGHS_INCLUDE_DIR})

          if(${HIGHS_INCLUDE_DIR} PATH_EQUAL ${HIGHS_SOURCE_DIR}/HiGHS/src)
              find_path(HIGHS_INCLUDE_BUILD HConfig.h
                PATHS
                ${HIGHS_SOURCE_DIR}/HiGHS/build
              )
              include_directories(${HIGHS_INCLUDE_BUILD})
          endif (${HIGHS_INCLUDE_DIR} PATH_EQUAL ${HIGHS_SOURCE_DIR}/HiGHS/src)

        add_executable(TestSolverIntegration testSolverInclusion.c)

        target_include_directories(TestSolverIntegration PRIVATE ${HIGHS_INCLUDE_DIR})

        target_link_libraries(TestSolverIntegration ${HIGHS_LIBRARIES})

        add_test(TestSolverIntegration TestSolverIntegration)

        add_executable(TestSolver testSolver.c ../src/model/TSPModel.c solvers/highsSolver.c)

        target_include_directories(TestSolver PRIVATE ${HIGHS_INCLUDE_DIR})

        add_test(TestSolver TestSolver)

        add_executable(TestWholeAlgorithm testWholeAlgorithm.c solvers/highsSolver.c)

        target_include_directories(TestWholeAlgorithm PRIVATE ${HIGHS_INCLUDE_DIR})

        add_test(TestWholeAlgorithm TestWholeAlgorithm)

        add_executable(TestAlgorithmMinDerivAllReconstructions testAlgorithmMinDerivAllReconstructions.c solvers/highsSolver.c)

        target_include_directories(TestAlgorithmMinDerivAllReconstructions PRIVATE ${HIGHS_INCLUDE_DIR})

        add_test(TestAlgorithmMinDerivAllReconstructions TestAlgorithmMinDerivAllReconstructions)

        add_executable(TestWholeAlgorithmSampled testWholeAlgorithm.c solvers/highsSolver.c)

        target_include_directories(TestWholeAlgorithmSampled PRIVATE ${HIGHS_INCLUDE_DIR})

        add_test(TestWholeAlgorithmSampled TestWholeAlgorithmSampled)

        add_executable(TestAlgorithmMinDerivAllReconstructionsSampled testAlgorithmMinDerivAllReconstructions.c solvers/highsSolver.c)

        target_include_directories(TestAlgorithmMinDerivAllReconstructionsSampled PRIVATE ${HIGHS_INCLUDE_DIR})

        add_test(TestAlgorithmMinDerivAllReconstructionsSampled TestAlgorithmMinDerivAllReconstructionsSampled)

        if(WIN32)
            target_link_libraries(TestSolver ${HIGHS_LIBRARIES})
            target_link_libraries(TestWholeAlgorithm TSPPartitionHeuristic ${HIGHS_LIBRARIES})
            target_link_libraries(TestAlgorithmMinDerivAllReconstructions TSPPartitionHeuristic ${HIGHS_LIBRARIES})
            target_link_libraries(TestWholeAlgorithmSampled TSPPartitionHeuristicSampled ${HIGHS_LIBRARIES})
            target_link_libraries(TestAlgorithmMinDerivAllReconstructionsSampled TSPPartitionHeuristicSampled ${HIGHS_LIBRARIES})
            target_compile_definitions(TestWholeAlgorithm PUBLIC WIN32)
            target_compile_definitions(TestWholeAlgorithmSampled PUBLIC WIN32 SAMPLER_ENABLED)
            target_compile_definitions(TestAlgorithmMinDerivAllReconstructionsSampled PUBLIC SAMPLER_ENABLED)
        else(WIN32)
            target_link_libraries(TestSolver ${HIGHS_LIBRARIES} m)
            target_link_libraries(TestWholeAlgorithm TSPPartitionHeuristic ${HIGHS_LIBRARIES} m)
            target_link_libraries(TestAlgorithmMinDerivAllReconstructions TSPPartitionHeuristic ${HIGHS_LIBRARIES} m)
            target_link_libraries(TestWholeAlgorithmSampled TSPPartitionHeuristicSampled ${HIGHS_LIBRARIES} m)
            target_link_libraries(TestAlgorithmMinDerivAllReconstructionsSampled TSPPartitionHeuristicSampled ${HIGHS_LIBRARIES} m)
            target_compile_definitions(TestWholeAlgorithm PUBLIC LINUX)
            target_compile_definitions(TestWholeAlgorithmSampled PUBLIC LINUX SAMPLER_ENABLED)
            target_compile_definitions(TestAlgorithmMinDerivAllReconstructionsSampled PUBLIC SAMPLER_ENABLED)
        endif(WIN32)  

    endif ()

endif ()
