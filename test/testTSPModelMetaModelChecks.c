#include "../src/model/model.h"

long *dummy_partition_distance_gen(struct TSP_instance *instance, struct partitions *partitions)
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
            else if(i < j)
            {
                unsigned firstPartitionIndex, secondPartitionIndex = 0;
                for (unsigned int k = i * slider ; k < (i+1) *  slider ; k++)
                {
                    if(partitions->partitionMap[k] == 1)
                    {
                        firstPartitionIndex = k % slider ;
                        goto SECOND_LOOP;
                    }
                }
                SECOND_LOOP :
                for (unsigned int k = j * slider ; k < (j+1) *  slider ; k++)
                {
                    if(partitions->partitionMap[k] == 1)
                    {
                        secondPartitionIndex = k % slider ;
                        goto COSTS;
                    }
                }
                COSTS:
                new_costs[i * partitions->partitions + j] = get_connection_cost(instance, firstPartitionIndex, secondPartitionIndex) ;
            }
            else
            {
                unsigned firstPartitionIndex, secondPartitionIndex = 0 ;
                for (unsigned int k = j * slider ; k < (j+1) *  slider ; k++)
                {
                    if(partitions->partitionMap[k] == 1)
                    {
                        firstPartitionIndex = k % slider ;
                        goto FOURTH_LOOP;
                    }
                }
                FOURTH_LOOP :
                for (unsigned int k = i * slider ; k < (i+1) *  slider ; k++)
                {
                    if(partitions->partitionMap[k] == 1)
                    {
                        secondPartitionIndex = k % slider ;
                        goto SECOND_COSTS;
                    }
                }
                SECOND_COSTS :
                new_costs[i * partitions->partitions + j] = get_connection_cost(instance, secondPartitionIndex, firstPartitionIndex) ;
            }
        }
    }

    return new_costs ;
}

int main(void)
{
    long costsMat[4][4] = {{0, 10, 20, 30},
                           {30, 0, 60, 20},
                           {5, 20, 0, 50},
                           {1,1,1,0}} ;

    struct TSP_instance *instance = create_instance(4, (long *)costsMat) ;

    unsigned char *adjacencies = instance->adjacencies ;

    *(adjacencies + 1) = 1 ;
    *(adjacencies + 4) = 1 ;
    *(adjacencies + 8 + 3) = 1 ;
    *(adjacencies + 12 + 2) = 1 ;

    struct meta_TSP_instance *metaTspInstance = generate_meta_instance(instance, dummy_partition_distance_gen) ;

    if(metaTspInstance->end->nodes != 2) return 1 ;

    long *costs = metaTspInstance->end->costs ;

    if(costs[0] != 0) return 1;
    if(costs[1] != 20) return 1;
    if(costs[2] != 5) return 1;
    if(costs[3] != 0) return 1;

    struct partitions *partitions = metaTspInstance->partitions ;

    if(partitions->partitions != 2) return 1 ;

    if(partitions->partitionMap[0] != 1) return 1 ;
    if(partitions->partitionMap[1] != 1) return 1 ;
    if(partitions->partitionMap[2] != 0) return 1 ;
    if(partitions->partitionMap[3] != 0) return 1 ;
    if(partitions->partitionMap[4] != 0) return 1 ;
    if(partitions->partitionMap[5] != 0) return 1 ;
    if(partitions->partitionMap[6] != 1) return 1 ;
    if(partitions->partitionMap[7] != 1) return 1 ;
    if(partitions->partitionMap[8] != 0) return 1 ;
    if(partitions->partitionMap[9] != 0) return 1 ;
    if(partitions->partitionMap[10] != 0) return 1 ;
    if(partitions->partitionMap[11] != 0) return 1 ;
    if(partitions->partitionMap[12] != 0) return 1 ;
    if(partitions->partitionMap[13] != 0) return 1 ;
    if(partitions->partitionMap[14] != 0) return 1 ;
    if(partitions->partitionMap[15] != 0) return 1 ;

    destroy_meta_instance(metaTspInstance) ;

    long fiveCostMat[5][5] = {{0, 10, 20, 30, 40},
                              {30, 0, 60, 20, 34},
                              {5, 20, 0, 50, 66},
                              {1,1,1,0, -4},
                              {4,7,5,-2,1}} ;

    instance = create_instance(5, (long *)fiveCostMat) ;

    adjacencies = instance->adjacencies ;

    *(adjacencies + 1) = 1 ;
    *(adjacencies + 5) = 1 ;
    *(adjacencies + 10 + 3) = 1 ;
    *(adjacencies + 15 + 4) = 1 ;
    *(adjacencies + 20 + 2) = 1 ;

    metaTspInstance = generate_meta_instance(instance, dummy_partition_distance_gen) ;

    if(metaTspInstance->end->nodes != 2) return 1 ;

    costs = metaTspInstance->end->costs ;

    if(costs[0] != 0) return 1;
    if(costs[1] != 20) return 1;
    if(costs[2] != 5) return 1;
    if(costs[3] != 0) return 1;

    partitions = metaTspInstance->partitions ;

    if(partitions->partitions != 2) return 1 ;

    if(partitions->partitionMap[0] != 1) return 1 ;
    if(partitions->partitionMap[1] != 1) return 1 ;
    if(partitions->partitionMap[2] != 0) return 1 ;
    if(partitions->partitionMap[3] != 0) return 1 ;
    if(partitions->partitionMap[4] != 0) return 1 ;
    if(partitions->partitionMap[5] != 0) return 1 ;
    if(partitions->partitionMap[6] != 0) return 1 ;
    if(partitions->partitionMap[7] != 1) return 1 ;
    if(partitions->partitionMap[8] != 1) return 1 ;
    if(partitions->partitionMap[9] != 1) return 1 ;
    if(partitions->partitionMap[10] != 0) return 1 ;
    if(partitions->partitionMap[11] != 0) return 1 ;
    if(partitions->partitionMap[12] != 0) return 1 ;
    if(partitions->partitionMap[13] != 0) return 1 ;
    if(partitions->partitionMap[14] != 0) return 1 ;
    if(partitions->partitionMap[15] != 0) return 1 ;
    if(partitions->partitionMap[16] != 0) return 1 ;
    if(partitions->partitionMap[17] != 0) return 1 ;
    if(partitions->partitionMap[18] != 0) return 1 ;
    if(partitions->partitionMap[19] != 0) return 1 ;
    if(partitions->partitionMap[20] != 0) return 1 ;
    if(partitions->partitionMap[21] != 0) return 1 ;
    if(partitions->partitionMap[22] != 0) return 1 ;
    if(partitions->partitionMap[23] != 0) return 1 ;
    if(partitions->partitionMap[24] != 0) return 1 ;

    destroy_meta_instance(metaTspInstance) ;

    return 0 ;
}