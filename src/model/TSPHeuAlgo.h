#ifndef MODEL_H
#error 'This file should not be included directly'
#endif

#define RELAXED 1
#define NOT_RELAXED 0
#include "model.h"

extern void TSP_heuristic_algorithm(struct TSP_instance *, long *distance_derivation_function(struct TSP_instance *, struct partitions *),
        void reconstruction_function(struct meta_TSP_instance *), void solver(struct TSP_instance *, unsigned char), unsigned int nodeThreshold) ;