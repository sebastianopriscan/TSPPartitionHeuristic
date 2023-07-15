#include "model.h"

long *min_derivation_function(struct TSP_instance *instance, struct partitions *partitions)
{
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    if((new_costs = malloc(sizeof(long) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in creating new cost matrix: ") ;
        exit(1) ;
    }

    for (unsigned int i = 0; i < partitions->partitions; i++) {
        for (unsigned int j = 0 ; j < partitions->partitions ; j++)
        {
            if(i == j)
            {
                new_costs[i * partitions->partitions + j] = 0 ;
            }
            else
            {
                long min_cost = LONG_MAX;
                for (unsigned int k1 = i * slider ; k1 < (i+1) * slider ; k1++)
                {
                    if(partitions->partitionMap[k1] == 0) continue ;

                    for (unsigned int k2 = j * slider; k2 < (j+1) * slider; k2++)
                    {
                        if(partitions->partitionMap[k2] == 0) continue ;

                        long candidate_cost = get_connection_cost(instance, k1 % slider, k2 % slider) ;

                        min_cost = candidate_cost < min_cost ? candidate_cost : min_cost ;
                    }
                }
                new_costs[i * partitions->partitions + j] = min_cost ;
            }
        }
    }

    return new_costs ;
}
long *max_derivation_function(struct TSP_instance *instance, struct partitions *partitions) {
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    if((new_costs = malloc(sizeof(long) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in creating new cost matrix: ") ;
        exit(1) ;
    }

    for (unsigned int i = 0; i < partitions->partitions; i++) {
        for (unsigned int j = 0 ; j < partitions->partitions ; j++)
        {
            if(i == j)
            {
                new_costs[i * partitions->partitions + j] = 0 ;
            }
            else
            {
                long max_cost = LONG_MIN;
                for (unsigned int k1 = i * slider ; k1 < (i+1) * slider ; k1++)
                {
                    if(partitions->partitionMap[k1] == 0) continue ;

                    for (unsigned int k2 = j * slider; k2 < (j+1) * slider; k2++)
                    {
                        if(partitions->partitionMap[k2] == 0) continue ;

                        long candidate_cost = get_connection_cost(instance, k1 % slider, k2 % slider) ;

                        max_cost = candidate_cost > max_cost ? candidate_cost : max_cost ;
                    }
                }
                new_costs[i * partitions->partitions + j] = max_cost ;
            }
        }
    }

    return new_costs ;
}
long *average_derivation_function(struct TSP_instance *instance, struct partitions *partitions)
{
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    if((new_costs = malloc(sizeof(long) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in creating new cost matrix: ") ;
        exit(1) ;
    }

    for (unsigned int i = 0; i < partitions->partitions; i++) {
        for (unsigned int j = 0 ; j < partitions->partitions ; j++)
        {
            if(i == j)
            {
                new_costs[i * partitions->partitions + j] = 0 ;
            }
            else
            {
                long costs_sum = 0 ;
                unsigned long iterations = 0 ;

                for (unsigned int k1 = i * slider ; k1 < (i+1) * slider ; k1++)
                {
                    if(partitions->partitionMap[k1] == 0) continue ;

                    for (unsigned int k2 = j * slider; k2 < (j+1) * slider; k2++)
                    {
                        if(partitions->partitionMap[k2] == 0) continue ;

                        costs_sum += get_connection_cost(instance, k1 % slider, k2 % slider) ;
                        iterations++ ;
                    }
                }
                new_costs[i * partitions->partitions + j] = costs_sum / iterations ;
            }
        }
    }

    return new_costs ;
}