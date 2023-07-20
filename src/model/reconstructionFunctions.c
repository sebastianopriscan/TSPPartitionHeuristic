#include "model.h"

void saving_reconstruction_function(struct meta_TSP_instance *metaTspInstance)
{
    struct TSP_instance *partitioned = metaTspInstance->end ;

    struct TSP_instance *original = metaTspInstance->start ;

    struct partitions *partitions = metaTspInstance->partitions ;

    for (unsigned int i = 0 ; i < partitioned->nodes * partitioned->nodes ; i++)
    {
        if(partitioned->adjacencies[i] == 1)
        {
            unsigned int firstIdx, secondIdx ;

            firstIdx = i / partitioned->nodes ;
            secondIdx = i % partitioned->nodes ;



            i += partitioned->nodes - secondIdx ;
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
                struct partition_indexes *actualEntrance = indexes + partActual * partitions->partitions + partPrev ;
                struct partition_indexes *actualExit = indexes + partActual * partitions->partitions + k ;
                struct partition_indexes *prev = indexes + partPrev * partitions->partitions + partActual ;
                struct partition_indexes *next = indexes + k * partitions->partitions + partActual ;

                unsigned long prevPartNode = partitions->partitionMap[partPrev * partitions->nodes + prev->exitIndex] ;
                unsigned long nextPartNode = partitions->partitionMap[k * partitions->nodes + next->entranceIndex] ;

                unsigned long entrance_node_idx = actualEntrance->entranceIndex, end_node_idx = actualExit->exitIndex ;

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
                    original->adjacencies[prevPartNode * original->nodes + entranceNode] = 1 ;
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
                original->adjacencies[prevPartNode * original->nodes + partitions->partitionMap[partActual * partitions->nodes + entrance_node_idx]] = 1 ;
                original->adjacencies[partitions->partitionMap[partActual * partitions->nodes + end_node_idx] * original->nodes + nextPartNode] = 1 ;

                partPrev = partActual ;
                partActual = k ;

                break;
            }
        }
    }
    while (partActual != partActual_original) ;
}

void max_reconstruction_function(struct meta_TSP_instance *metaTspInstance)
{
    struct TSP_instance *partitioned = metaTspInstance->end ;

    struct TSP_instance *original = metaTspInstance->start ;

    struct partitions *partitions = metaTspInstance->partitions ;

    for (unsigned int i = 0 ; i < partitioned->nodes * partitioned->nodes ; i++)
    {
        if(partitioned->adjacencies[i] == 1)
        {
            unsigned int firstIdx, secondIdx ;

            firstIdx = i / partitioned->nodes ;
            secondIdx = i % partitioned->nodes ;



            i += partitioned->nodes - secondIdx ;
        }
    }
}