#include "model.h"

long *min_derivation_function_minRec(struct TSP_instance *instance, struct partitions *partitions)
{
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    struct partition_indexes *indexes ;

    if((indexes = malloc(sizeof(struct partition_indexes) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    partitions->metadata = indexes ;

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
                indexes[i * partitions->partitions + j].exitIndex = ULONG_MAX ;
                indexes[j * partitions->partitions + i].entranceIndex = ULONG_MAX ;
            }
            else
            {
                long min_cost = LONG_MAX;
                unsigned long bestEntranceIndex, bestExitIndex ;

                unsigned int firstPartIndex = 0, secondPartIndex = 0 ;
                while (partitions->partitionMap[i * slider + firstPartIndex] != ULONG_MAX)
                {
                    while (partitions->partitionMap[j * slider + secondPartIndex] != ULONG_MAX)
                    {
                        long candidate_cost = get_connection_cost(instance,
                          partitions->partitionMap[i * slider + firstPartIndex], partitions->partitionMap[j * slider + secondPartIndex]) ;

                        if(candidate_cost < min_cost)
                        {
                            min_cost = candidate_cost ;
                            bestExitIndex = firstPartIndex ;
                            bestEntranceIndex = secondPartIndex ;
                        }
                        secondPartIndex++ ;
                    }
                    secondPartIndex = 0 ;
                    firstPartIndex++ ;
                }

                new_costs[i * partitions->partitions + j] = min_cost ;

                indexes[i * partitions->partitions + j].exitIndex = bestExitIndex ;
                indexes[j * partitions->partitions + i].entranceIndex = bestEntranceIndex ;
            }
        }
    }

    return new_costs ;
}

long *max_derivation_function_minRec(struct TSP_instance *instance, struct partitions *partitions)
{
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    if((new_costs = malloc(sizeof(long) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in creating new cost matrix: ") ;
        exit(1) ;
    }

    struct partition_indexes *indexes ;

    if((indexes = malloc(sizeof(struct partition_indexes) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    partitions->metadata = indexes ;

    for (unsigned int i = 0; i < partitions->partitions; i++) {
        for (unsigned int j = 0 ; j < partitions->partitions ; j++)
        {
            if(i == j)
            {
                new_costs[i * partitions->partitions + j] = 0 ;
                indexes[i * partitions->partitions + j].exitIndex = ULONG_MAX ;
                indexes[j * partitions->partitions + i].entranceIndex = ULONG_MAX ;
            }
            else
            {
                long max_cost = LONG_MIN;
                long min_cost = LONG_MAX;

                unsigned int firstPartIndex = 0, secondPartIndex = 0 ;
                unsigned long bestEntranceIndex, bestExitIndex ;

                while (partitions->partitionMap[i * slider + firstPartIndex] != ULONG_MAX)
                {
                    while (partitions->partitionMap[j * slider + secondPartIndex] != ULONG_MAX)
                    {
                        long candidate_cost = get_connection_cost(instance,
                              partitions->partitionMap[i * slider + firstPartIndex], partitions->partitionMap[j * slider + secondPartIndex]) ;

                        max_cost = candidate_cost > max_cost ? candidate_cost : max_cost ;

                        if(candidate_cost < min_cost)
                        {
                            min_cost = candidate_cost ;
                            bestExitIndex = firstPartIndex ;
                            bestEntranceIndex = secondPartIndex ;
                        }

                        secondPartIndex++ ;
                    }
                    secondPartIndex = 0 ;
                    firstPartIndex++ ;
                }

                new_costs[i * partitions->partitions + j] = max_cost ;

                indexes[i * partitions->partitions + j].exitIndex = bestExitIndex ;
                indexes[j * partitions->partitions + i].entranceIndex = bestEntranceIndex ;
            }
        }
    }

    return new_costs ;
}

long *average_derivation_function_minRec(struct TSP_instance *instance, struct partitions *partitions)
{
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    if((new_costs = malloc(sizeof(long) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in creating new cost matrix: ") ;
        exit(1) ;
    }

    struct partition_indexes *indexes ;

    if((indexes = malloc(sizeof(struct partition_indexes) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    partitions->metadata = indexes ;

    for (unsigned int i = 0; i < partitions->partitions; i++) {
        for (unsigned int j = 0 ; j < partitions->partitions ; j++)
        {
            if(i == j)
            {
                new_costs[i * partitions->partitions + j] = 0 ;
                indexes[i * partitions->partitions + j].exitIndex = ULONG_MAX ;
                indexes[j * partitions->partitions + i].entranceIndex = ULONG_MAX ;
            }
            else
            {
                long costs_sum = 0 ;
                long iterations = 0 ;
                long min_cost = LONG_MAX;

                unsigned int firstPartIndex = 0, secondPartIndex = 0 ;
                unsigned long bestEntranceIndex, bestExitIndex ;

                while (partitions->partitionMap[i * slider + firstPartIndex] != ULONG_MAX)
                {
                    while (partitions->partitionMap[j * slider + secondPartIndex] != ULONG_MAX)
                    {
                        long candidate_cost = get_connection_cost(instance,
                                  partitions->partitionMap[i * slider + firstPartIndex], partitions->partitionMap[j * slider + secondPartIndex]) ;

                        costs_sum += candidate_cost ;

                        iterations++ ;

                        if(candidate_cost < min_cost)
                        {
                            min_cost = candidate_cost ;
                            bestExitIndex = firstPartIndex ;
                            bestEntranceIndex = secondPartIndex ;
                        }

                        secondPartIndex++ ;
                    }
                    secondPartIndex = 0 ;
                    firstPartIndex++ ;
                }

                new_costs[i * partitions->partitions + j] = costs_sum / iterations ;

                indexes[i * partitions->partitions + j].exitIndex = bestExitIndex ;
                indexes[j * partitions->partitions + i].entranceIndex = bestEntranceIndex ;
            }
        }
    }

    return new_costs ;
}

long *min_derivation_function_saving(struct TSP_instance *instance, struct partitions *partitions)
{
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    long *distances_scoreboard ;

    if((distances_scoreboard = malloc(sizeof(long) * partitions->nodes)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    for (unsigned long i = 0 ; i < instance->nodes ; i++)
    {
        distances_scoreboard[i] = LONG_MIN ;
    }

    struct partition_indexes *indexes ;

    if((indexes = malloc(sizeof(struct partition_indexes) * partitions->partitions * partitions->partitions * instance->nodes)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    partitions->metadata = indexes ;

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

                unsigned int firstPartIndex = 0, secondPartIndex = 0 ;

                while (partitions->partitionMap[i * slider + firstPartIndex] != ULONG_MAX)
                {
                    long node_min_cost = LONG_MAX ;
                    unsigned long min_node_idx = 0 ;

                    while (partitions->partitionMap[j * slider + secondPartIndex] != ULONG_MAX)
                    {
                        long candidate_cost = get_connection_cost(instance,
                                          partitions->partitionMap[i * slider + firstPartIndex], partitions->partitionMap[j * slider + secondPartIndex]) ;

                        if(candidate_cost < min_cost)
                        {
                            min_cost = candidate_cost ;
                        }

                        if(candidate_cost < node_min_cost)
                        {
                            node_min_cost = candidate_cost ;
                            min_node_idx = secondPartIndex ;
                        }

                        secondPartIndex++ ;
                    }

                    indexes[i * partitions->partitions * instance->nodes + j * instance->nodes + firstPartIndex].exitIndex = min_node_idx ;

                    long cost = get_connection_cost(instance, partitions->partitionMap[i * partitions->nodes + firstPartIndex],
                                                    partitions->partitionMap[j * partitions->nodes + min_node_idx]) ;

                    unsigned long arrivalNode = partitions->partitionMap[j * partitions->nodes + min_node_idx] ;

                    if(cost > distances_scoreboard[arrivalNode])
                    {
                        distances_scoreboard[arrivalNode] = cost ;
                        indexes[j * partitions->partitions * instance->nodes + i * instance->nodes + min_node_idx].entranceIndex = firstPartIndex ;
                    }

                    secondPartIndex = 0 ;
                    firstPartIndex++ ;
                }

                new_costs[i * partitions->partitions + j] = min_cost ;

                unsigned long partIdx = 0 ;

                while (partitions->partitionMap[j * partitions->nodes + partIdx] != ULONG_MAX)
                {
                    distances_scoreboard[partitions->partitionMap[j * partitions->nodes + partIdx]] = LONG_MIN ;
                    partIdx++ ;
                }
            }
        }
    }

    return new_costs ;
}

long *max_derivation_function_saving(struct TSP_instance *instance, struct partitions *partitions)
{
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    long *distances_scoreboard ;

    if((distances_scoreboard = malloc(sizeof(long) * partitions->nodes)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    for (unsigned long i = 0 ; i < instance->nodes ; i++)
    {
        distances_scoreboard[i] = LONG_MIN ;
    }

    if((new_costs = malloc(sizeof(long) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in creating new cost matrix: ") ;
        exit(1) ;
    }

    struct partition_indexes *indexes ;

    if((indexes = malloc(sizeof(struct partition_indexes) * partitions->partitions * partitions->partitions * instance->nodes)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    partitions->metadata = indexes ;

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

                unsigned int firstPartIndex = 0, secondPartIndex = 0 ;

                while (partitions->partitionMap[i * slider + firstPartIndex] != ULONG_MAX)
                {
                    long node_min_cost = LONG_MAX ;
                    unsigned long min_node_idx = 0 ;

                    while (partitions->partitionMap[j * slider + secondPartIndex] != ULONG_MAX)
                    {
                        long candidate_cost = get_connection_cost(instance,
                                          partitions->partitionMap[i * slider + firstPartIndex], partitions->partitionMap[j * slider + secondPartIndex]) ;

                        max_cost = candidate_cost > max_cost ? candidate_cost : max_cost ;

                        if(candidate_cost < node_min_cost)
                        {
                            node_min_cost = candidate_cost ;
                            min_node_idx = secondPartIndex ;
                        }

                        secondPartIndex++ ;
                    }

                    indexes[i * partitions->partitions * instance->nodes + j * instance->nodes + firstPartIndex].exitIndex = min_node_idx ;

                    long cost = get_connection_cost(instance, partitions->partitionMap[i * partitions->nodes + firstPartIndex],
                                                    partitions->partitionMap[j * partitions->nodes + min_node_idx]) ;

                    unsigned long arrivalNode = partitions->partitionMap[j * partitions->nodes + min_node_idx] ;

                    if(cost > distances_scoreboard[arrivalNode])
                    {
                        distances_scoreboard[arrivalNode] = cost ;
                        indexes[j * partitions->partitions * instance->nodes + i * instance->nodes + min_node_idx].entranceIndex = firstPartIndex ;
                    }

                    secondPartIndex = 0 ;
                    firstPartIndex++ ;
                }

                new_costs[i * partitions->partitions + j] = max_cost ;

                unsigned long partIdx = 0 ;

                while (partitions->partitionMap[j * partitions->nodes + partIdx] != ULONG_MAX)
                {
                    distances_scoreboard[partitions->partitionMap[j * partitions->nodes + partIdx]] = LONG_MIN ;
                    partIdx++ ;
                }
            }
        }
    }

    return new_costs ;
}

long *average_derivation_function_saving(struct TSP_instance *instance, struct partitions *partitions)
{
    unsigned int slider = partitions->nodes ;
    long *new_costs ;

    long *distances_scoreboard ;

    if((distances_scoreboard = malloc(sizeof(long) * partitions->nodes)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    for (unsigned long i = 0 ; i < instance->nodes ; i++)
    {
        distances_scoreboard[i] = LONG_MIN ;
    }

    if((new_costs = malloc(sizeof(long) * partitions->partitions * partitions->partitions)) == NULL)
    {
        perror("Error in creating new cost matrix: ") ;
        exit(1) ;
    }

    struct partition_indexes *indexes ;

    if((indexes = malloc(sizeof(struct partition_indexes) * partitions->partitions * partitions->partitions * instance->nodes)) == NULL)
    {
        perror("Error in allocating resources: ") ;
        exit(1) ;
    }

    partitions->metadata = indexes ;

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
                long iterations = 0 ;

                unsigned int firstPartIndex = 0, secondPartIndex = 0 ;

                while (partitions->partitionMap[i * slider + firstPartIndex] != ULONG_MAX)
                {
                    long node_min_cost = LONG_MAX ;
                    unsigned long min_node_idx = 0 ;

                    while (partitions->partitionMap[j * slider + secondPartIndex] != ULONG_MAX)
                    {
                        long candidate_cost = get_connection_cost(instance,
                                                                  partitions->partitionMap[i * slider + firstPartIndex], partitions->partitionMap[j * slider + secondPartIndex]) ;

                        costs_sum += candidate_cost ;

                        iterations++ ;

                        if(candidate_cost < node_min_cost)
                        {
                            node_min_cost = candidate_cost ;
                            min_node_idx = secondPartIndex ;
                        }

                        secondPartIndex++ ;
                    }

                    indexes[i * partitions->partitions * instance->nodes + j * instance->nodes + firstPartIndex].exitIndex = min_node_idx ;

                    long cost = get_connection_cost(instance, partitions->partitionMap[i * partitions->nodes + firstPartIndex],
                                                    partitions->partitionMap[j * partitions->nodes + min_node_idx]) ;

                    unsigned long arrivalNode = partitions->partitionMap[j * partitions->nodes + min_node_idx] ;

                    if(cost > distances_scoreboard[arrivalNode])
                    {
                        distances_scoreboard[arrivalNode] = cost ;
                        indexes[j * partitions->partitions * instance->nodes + i * instance->nodes + min_node_idx].entranceIndex = firstPartIndex ;
                    }

                    secondPartIndex = 0 ;
                    firstPartIndex++ ;
                }

                new_costs[i * partitions->partitions + j] = costs_sum / iterations ;

                unsigned long partIdx = 0 ;

                while (partitions->partitionMap[j * partitions->nodes + partIdx] != ULONG_MAX)
                {
                    distances_scoreboard[partitions->partitionMap[j * partitions->nodes + partIdx]] = LONG_MIN ;
                    partIdx++ ;
                }
            }
        }
    }

    return new_costs ;
}