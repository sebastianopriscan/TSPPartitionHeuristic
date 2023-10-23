#include "model.h"

void saving_reconstruction_function(struct meta_TSP_instance *metaTspInstance)
{
    struct TSP_instance *partitioned = metaTspInstance->end ;

    struct TSP_instance *original = metaTspInstance->start ;

    struct partitions *partitions = metaTspInstance->partitions ;

    struct partition_indexes *indexes = (struct partition_indexes *) partitions->metadata ;

    unsigned long start_partition_Idx = 0, start_node_idx = 0, next_node_idx ;
    long min_saving = LONG_MAX ;

    for (unsigned int i = 0 ; i < partitioned->nodes * partitioned->nodes ; i++)
    {
        if(partitioned->adjacencies[i] == 1)
        {
            unsigned int firstIdx, secondIdx, thirdIdx;

            firstIdx = i / partitioned->nodes ;
            secondIdx = i % partitioned->nodes ;

            thirdIdx = 0 ;

            while(get_nodes_adjacency(partitioned, secondIdx, thirdIdx) != 1)
            {
                thirdIdx++ ;
            }

            unsigned long in_partition_Idx = 0 ;

            while (partitions->partitionMap[secondIdx * partitions->nodes + in_partition_Idx] != ULONG_MAX)
            {
                unsigned long nextIdx = partitions->partitionMap[secondIdx * partitions->nodes + in_partition_Idx +1] != ULONG_MAX ? in_partition_Idx +1 : 0 ;
                unsigned long nextNode = partitions->partitionMap[secondIdx * partitions->nodes + nextIdx] ;

                long arc_cost = get_connection_cost(original, partitions->partitionMap[secondIdx * partitions->nodes + in_partition_Idx], nextNode) ;

                unsigned long entrance_index = indexes[secondIdx * partitions->partitions * partitions->nodes + firstIdx * partitions->nodes + nextIdx].entranceIndex ;
                unsigned long exit_index = indexes[secondIdx * partitions->partitions * partitions->nodes + thirdIdx * partitions->nodes + in_partition_Idx].exitIndex ;

                long entrance_cost = get_connection_cost(original, partitions->partitionMap[firstIdx * partitions->nodes + entrance_index], nextNode) ;
                long exit_cost = get_connection_cost(original, partitions->partitionMap[secondIdx * partitions->nodes + in_partition_Idx],
                                                     partitions->partitionMap[thirdIdx * partitions->nodes + exit_index]) ;

                long saving = entrance_cost + exit_cost - arc_cost ;

                if(saving < min_saving)
                {
                    min_saving = saving ;
                    start_partition_Idx = secondIdx ;
                    start_node_idx = in_partition_Idx ;
                    next_node_idx = nextIdx ;
                }

                in_partition_Idx++ ;
            }

            i += partitioned->nodes - secondIdx ;
        }
    }

    unsigned long node_index = start_node_idx, next_node_index = next_node_idx, partition_index = start_partition_Idx, counter = 0 ;

    NEXT_PART_LOOP :
    for(unsigned long i = 0 ; i < partitioned->nodes ; i++)
    {
        if(get_nodes_adjacency(partitioned, partition_index, i) == 1)
        {
            unsigned long first_node = partitions->partitionMap[partition_index * partitions->nodes + node_index] ;
            unsigned long second_node = partitions->partitionMap[partition_index * partitions->nodes + next_node_index] ;

            original->adjacencies[first_node * original->nodes + second_node] = 0 ;

            if(counter != partitioned->nodes -1)
            {
                unsigned long arrival_index = indexes[partition_index * partitions->partitions * original->nodes + i * original->nodes + node_index].exitIndex ;
                unsigned long arrival_node = partitions->partitionMap[i * partitions->nodes + arrival_index] ;

                original->adjacencies[first_node * original->nodes + arrival_node] = 1 ;

                next_node_index = arrival_index ;
                partition_index = i ;

                if(arrival_index != 0)
                {
                    node_index = arrival_index -1 ;
                }
                else
                {
                    unsigned long p = 2;
                    while(partitions->partitionMap[i * partitions->nodes + p] != ULONG_MAX) p++ ;

                    node_index = p -1 ;
                }

                counter++ ;
                goto NEXT_PART_LOOP ;
            }

            unsigned long start_next_node = partitions->partitionMap[start_partition_Idx * partitions->nodes + next_node_idx] ;
            original->adjacencies[first_node * original->nodes + start_next_node] = 1 ;

            break ;
        }
    }
}

void min_reconstruction_function(struct meta_TSP_instance *metaTspInstance)
{
    struct TSP_instance *partitioned = metaTspInstance->end ;

    struct TSP_instance *original = metaTspInstance->start ;

    struct partitions *partitions = metaTspInstance->partitions ;

    struct partition_indexes *indexes = partitions->metadata ;

    unsigned long partPrev = 0, partActual, partActual_original ;

    for (unsigned int k = 0 ; k < partitioned->nodes ; k++)
    {
        if(get_nodes_adjacency(partitioned, partPrev, k) == 1)
        {
            partActual = k ;
            partActual_original = k ;
            break ;
        }
    }

    do {

        for (unsigned int k = 0 ; k < partitioned->nodes ; k++)
        {
            if(get_nodes_adjacency(partitioned, partActual, k) == 1)
            {
                //The commented out lines in this scope are thought to be redundant, they will be kept until sure
                struct partition_indexes *actualEntrance = indexes + partActual * partitions->partitions + partPrev ;
                struct partition_indexes *actualExit = indexes + partActual * partitions->partitions + k ;
                struct partition_indexes *prev = indexes + partPrev * partitions->partitions + partActual ;
                struct partition_indexes *next = indexes + k * partitions->partitions + partActual ;

                unsigned long prevPartNode = partitions->partitionMap[partPrev * partitions->nodes + prev->exitIndex] ;
                unsigned long nextPartNode = partitions->partitionMap[k * partitions->nodes + next->entranceIndex] ;

                unsigned long entrance_node_idx = actualEntrance->entranceIndex, end_node_idx = actualExit->exitIndex ;

                if(entrance_node_idx == end_node_idx)
                {
                    unsigned int entrance_champion_idx , exit_champion_idx ;
                    long entrance_champion_cost = LONG_MAX, exit_champion_cost = LONG_MAX ;
                    unsigned int partIndex = 0;

                    while(partitions->partitionMap[partActual * partitions->nodes + partIndex] != ULONG_MAX)
                    {
                        if(partIndex != entrance_node_idx)
                        {
                            long candidate_entrance_cost, candidate_exit_cost ;

                            candidate_entrance_cost = get_connection_cost(original, prevPartNode,
                                  partitions->partitionMap[partActual * partitions->nodes + partIndex]) ;
                            candidate_exit_cost = get_connection_cost(original, partitions->partitionMap[partActual * partitions->nodes + partIndex],
                                              nextPartNode) ;

                            if(candidate_entrance_cost < entrance_champion_cost)
                            {
                                entrance_champion_cost = candidate_entrance_cost ;
                                entrance_champion_idx = partIndex ;
                            }

                            if(candidate_exit_cost < exit_champion_cost)
                            {
                                exit_champion_cost = candidate_exit_cost ;
                                exit_champion_idx = partIndex ;
                            }
                        }
                        partIndex++ ;
                    }

                    long past_entrance_cost = get_connection_cost(original, prevPartNode, partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx]) ;
                    long past_exit_cost = get_connection_cost(original, partitions->partitionMap[partActual * partitions->nodes + end_node_idx], nextPartNode) ;

                    if(entrance_champion_cost + past_exit_cost < exit_champion_cost + past_entrance_cost)
                    {
                        if(partPrev != 0)
                        {
                            original->adjacencies[prevPartNode * partitions->nodes + partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx]] = 0 ;
                        }
                        else
                            indexes[partActual * partitions->partitions + partPrev].entranceIndex = entrance_champion_idx ;
                        entrance_node_idx = entrance_champion_idx ;
                        original->adjacencies[prevPartNode * partitions->nodes + partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx]] = 1 ;
                    }
                    else
                    {
                        indexes[partActual * partitions->partitions + k].exitIndex = exit_champion_idx ;
                        end_node_idx = exit_champion_idx ;
                    }
                }

                unsigned long attached_start, attached_end ;

                attached_start = partitions->partitionMap[partActual * partitions->nodes + end_node_idx +1] != ULONG_MAX
                        ? partitions->partitionMap[partActual * partitions->nodes + end_node_idx +1] : partitions->partitionMap[partActual * partitions->nodes] ;

                if(entrance_node_idx != 0)
                {
                    attached_end = partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx -1] ;
                } else
                {
                    int j = 0 ;
                    while (partitions->partitionMap[partActual * partitions->nodes + j] != ULONG_MAX)
                    {
                        j++ ;
                    }

                    attached_end = partitions->partitionMap[partActual * partitions->nodes + j -1] ;
                }

                if(attached_start == partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx])
                {
                    unsigned long entranceNode = partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx] ;
                    unsigned long exitNode = partitions->partitionMap[partActual * partitions->nodes + end_node_idx] ;
                    original->adjacencies[exitNode * original->nodes + entranceNode] = 0 ;
                    //original->adjacencies[prevPartNode * original->nodes + entranceNode] = 1 ;
                    original->adjacencies[exitNode * original->nodes + nextPartNode] = 1 ;

                    partPrev = partActual ;
                    partActual = k ;

                    break;
                }

                unsigned long attach_start, attach_end ;
                long top_saving = LONG_MAX ;

                unsigned int actual_index = entrance_node_idx ;

                while (actual_index != end_node_idx)
                {
                    unsigned long nextNodeIndex = partitions->partitionMap[partActual * partitions->nodes + actual_index +1] != ULONG_MAX
                                                  ?  actual_index +1 : 0 ;

                    unsigned long nextNode = partitions->partitionMap[partActual * partitions->nodes + nextNodeIndex] ;

                    long saving = get_connection_cost(original, partitions->partitionMap[partActual * partitions->nodes + actual_index], attached_start)
                                  + get_connection_cost(original,attached_end, nextNode)
                                  - get_connection_cost(original, partitions->partitionMap[partActual * partitions->nodes + actual_index], nextNode) ;
                    if(saving < top_saving)
                    {
                        attach_start = partitions->partitionMap[partActual * partitions->nodes + actual_index] ;
                        attach_end = nextNode ;
                    }

                    actual_index = nextNodeIndex ;
                }

                original->adjacencies[attach_start * original->nodes + attach_end] = 0 ;
                original->adjacencies[attached_end * original->nodes + partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx]] = 0 ;
                original->adjacencies[partitions->partitionMap[partActual * partitions->nodes + end_node_idx] * original->nodes + attached_start] = 0 ;
                original->adjacencies[attach_start * original->nodes + attached_start] = 1 ;
                original->adjacencies[attached_end * original->nodes + attach_end] = 1 ;
                //original->adjacencies[prevPartNode * original->nodes + partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx]] = 1 ;
                original->adjacencies[partitions->partitionMap[partActual * partitions->nodes + end_node_idx] * original->nodes + nextPartNode] = 1 ;

                partPrev = partActual ;
                partActual = k ;

                break;
            }
        }
    }
    while (partActual != partActual_original) ;
}