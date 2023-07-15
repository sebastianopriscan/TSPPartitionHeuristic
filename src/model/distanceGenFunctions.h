#ifndef MODEL_H
#error 'This file should not be included directly'
#endif

#include "model.h"

extern long *min_derivation_function(struct TSP_instance *, struct partitions *) ;
extern long *max_derivation_function(struct TSP_instance *, struct partitions *) ;
extern long *average_derivation_function(struct TSP_instance *, struct partitions *) ;