#include "model.h"

void TSP_heuristic_algorithm(struct TSP_instance *instance, long *distance_derivation_function(struct TSP_instance *, struct partitions *),
        void reconstruction_function(struct meta_TSP_instance *), void solver(struct TSP_instance *, unsigned char relaxed), unsigned int nodeThreshold)
{
    if(instance->nodes <= nodeThreshold)
    {
        solver(instance, NOT_RELAXED) ;
        return ;
    }
    else
    {
        solver(instance, RELAXED) ;

        if(check_instance_connection(instance) == 0) return ;

        struct meta_TSP_instance *metaTspInstance = generate_meta_instance(instance, distance_derivation_function) ;

        TSP_heuristic_algorithm(metaTspInstance->end, distance_derivation_function, reconstruction_function, solver, nodeThreshold) ;

        reconstruction_function(metaTspInstance) ;

        return ;
    }
}