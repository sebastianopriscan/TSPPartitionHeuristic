#ifndef MODEL_H
#error 'This file should not be included directly'
#endif

#include "model.h"

extern long *min_derivation_function_minRec(struct TSP_instance *instance, struct partitions *partitions) ;
extern long *max_derivation_function_minRec(struct TSP_instance *instance, struct partitions *partitions) ;
extern long *average_derivation_function_minRec(struct TSP_instance *instance, struct partitions *partitions) ;

extern long *min_derivation_function_saving(struct TSP_instance *instance, struct partitions *partitions) ;
extern long *max_derivation_function_saving(struct TSP_instance *instance, struct partitions *partitions) ;
extern long *average_derivation_function_saving(struct TSP_instance *instance, struct partitions *partitions) ;