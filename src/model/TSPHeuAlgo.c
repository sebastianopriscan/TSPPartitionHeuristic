#include "model.h"
#ifdef SAMPLER_ENABLED
#include "../sampler/sampler.h"
#include <time.h>
#endif


void TSP_heuristic_algorithm(struct TSP_instance *instance, long *distance_derivation_function(struct TSP_instance *, struct partitions *),
        void reconstruction_function(struct meta_TSP_instance *), void solver(struct TSP_instance *, unsigned char relaxed), unsigned int nodeThreshold)
{

#ifdef SAMPLER_ENABLED
    increaseRecursiveSteps() ;
    registerInstanceCosts(instance->costs, instance->nodes) ;
#endif
    
    if(instance->nodes <= nodeThreshold)
    {
#ifdef SAMPLER_ENABLED
        clock_t start_ticks = clock() ;
#endif
        solver(instance, NOT_RELAXED) ;
#ifdef SAMPLER_ENABLED
        clock_t end_ticks = clock() ;
        registerTimeSpentInSolver(end_ticks - start_ticks) ;
        registerInstanceAdjacencies(instance->adjacencies, instance->nodes) ;
#endif
        return ;
    }
    else
    {
#ifdef SAMPLER_ENABLED
        clock_t solver_start = clock() ;
#endif
        solver(instance, RELAXED) ;
#ifdef SAMPLER_ENABLED
        clock_t solver_end = clock() ;
        registerTimeSpentInSolver(solver_end - solver_start) ;
#endif

        if(check_instance_connection(instance) == 0) {
#ifdef SAMPLER_ENABLED
            registerInstanceAdjacencies(instance->adjacencies, instance->nodes) ;
#endif
            return ;
        } 

#ifdef SAMPLER_ENABLED
        clock_t derivation_start = clock() ;
#endif
        struct meta_TSP_instance *metaTspInstance = generate_meta_instance(instance, distance_derivation_function) ;
#ifdef SAMPLER_ENABLED
        clock_t derivation_end = clock() ;
        registerTimeSpentInDerivation(derivation_end - derivation_start) ;
        registerPartitions(metaTspInstance->partitions->partitionMap, instance->nodes) ;
#endif
        TSP_heuristic_algorithm(metaTspInstance->end, distance_derivation_function, reconstruction_function, solver, nodeThreshold) ;

#ifdef SAMPLER_ENABLED
        clock_t reconstruction_start = clock() ;
#endif
        reconstruction_function(metaTspInstance) ;
#ifdef SAMPLER_ENABLED
        clock_t reconstruction_end = clock() ;
        registerTimeSpentInReconstruction(reconstruction_end - reconstruction_start) ;
        registerInstanceAdjacencies(instance->adjacencies, instance->nodes) ;
#endif

        destroy_meta_instance(metaTspInstance) ;

        return ;
    }
}