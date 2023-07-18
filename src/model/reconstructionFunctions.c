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

    unsigned short partitionedSequence[partitioned->nodes] ;
    unsigned short entranceNodes[partitioned->nodes] ;
    unsigned short exitNodes[partitioned->nodes] ;

    partitionedSequence[0] = 0 ;

    unsigned int seqIdx = 0 ;

    LOOP_START :

    for (unsigned int i = 0 ; i < partitioned->nodes ; i++)
    {
        if(seqIdx < partitioned->nodes && get_nodes_adjacency(partitioned, partitionedSequence[seqIdx],i) == 1)
        {
            seqIdx++ ;
            partitionedSequence[seqIdx] = i ;
            goto LOOP_START ;
        }
    }

    for (unsigned int i = 1, trials = 0  ; trials < (partitioned->nodes +1) / 2 ; i+= 2, trials++)
    {
        unsigned int prev = partitionedSequence[(int)i -1 == -1 ? partitioned->nodes -1 : i-1] ;
        unsigned int next = partitionedSequence[(i+1) % partitioned->nodes] ;
        unsigned int actual = partitionedSequence[i % partitioned->nodes] ;

        for(unsigned int j = 0 ; j < partitions->nodes ; j++)
        {
            for(unsigned int k = 0 ; k < partitions->nodes ; k++)
            {
                if(partitions->partitionMap[prev * partitioned->nodes + j] == 1 && partitions->partitionMap[actual * partitioned->nodes + k] == 1)
                {
                    long cost = get_connection_cost(original, j, k) ;
                    if(cost == get_connection_cost(partitioned, prev, actual))
                    {
                        entranceNodes[i % partitioned->nodes] = k ;
                        exitNodes[(int)i -1 == -1 ? partitioned->nodes -1 : i-1] = j ;
                    }
                }

                if(partitions->partitionMap[actual * partitioned->nodes + j] == 1 && partitions->partitionMap[next * partitioned->nodes + k] == 1)
                {
                    long cost = get_connection_cost(original, j, k) ;
                    if(cost == get_connection_cost(partitioned, actual, next))
                    {
                        exitNodes[i % partitioned->nodes] = j ;
                        entranceNodes[(i+1) % partitioned->nodes] = k ;
                    }
                }
            }
        }
    }

    for (unsigned int i = 1 ; i < partitioned->nodes ; i++)
    {
        unsigned long partitionSequence[partitions->nodes] ;
        unsigned long cycle_end, end_node_idx, attach_start, attach_end ;
        long top_saving = LONG_MAX ;

        partitionSequence[0] = entranceNodes[i] ;
        unsigned int idx = 0 ;

        PART_LOOP :
        for (unsigned int j = 0 ; j < partitions->nodes ; j++)
        {
            if(get_nodes_adjacency(original, partitionSequence[idx], j) == 1)
            {
                if(j == entranceNodes[i])
                {
                    cycle_end = idx ;
                    break;
                }

                idx++ ;
                partitionSequence[idx] = j ;

                if(j == exitNodes[i])
                {
                    end_node_idx = idx ;
                }

                goto PART_LOOP ;
            }
        }

        for(unsigned int j = 0 ; j < end_node_idx ; j++)
        {
            long saving = get_connection_cost(original, partitionSequence[j], partitionSequence[end_node_idx+1])
                    + get_connection_cost(original,partitionSequence[cycle_end], partitionSequence[j+1])
                    - get_connection_cost(original, partitionSequence[j], partitionSequence[j+1]) ;
            if(saving < top_saving)
            {
                attach_start = partitionSequence[j] ;
                attach_end = partitionSequence[j+1] ;
            }
        }

        original->adjacencies[attach_start * original->nodes + attach_end] = 0 ;
        original->adjacencies[partitionSequence[cycle_end] * original->nodes + partitionSequence[0]] = 0 ;
        original->adjacencies[partitionSequence[end_node_idx] * original->nodes + partitionSequence[end_node_idx +1]] = 0 ;
        original->adjacencies[attach_start * original->nodes + partitionSequence[end_node_idx +1]] = 1 ;
        original->adjacencies[partitionSequence[cycle_end] * original->nodes + attach_end] = 1 ;
        original->adjacencies[exitNodes[i-1] * original->nodes + partitionSequence[0]] = 1 ;
        original->adjacencies[partitionSequence[end_node_idx] * original->nodes + entranceNodes[(i+1) % partitioned->nodes]] = 1 ;
    }
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