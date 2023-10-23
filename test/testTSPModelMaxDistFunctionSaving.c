#include "../src/model/model.h"

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

    struct meta_TSP_instance *metaTspInstance = generate_meta_instance(instance, max_derivation_function_saving) ;

    if(metaTspInstance->end->nodes != 2) return 1 ;

    long *costs = metaTspInstance->end->costs ;

    if(costs[0] != 0) return 1;
    if(costs[1] != 60) return 1;
    if(costs[2] != 20) return 1;
    if(costs[3] != 0) return 1;

    struct partitions *partitions = metaTspInstance->partitions ;

    if(partitions->partitions != 2) return 1 ;

    if(partitions->partitionMap[0] != 0) return 1 ;
    if(partitions->partitionMap[1] != 1) return 1 ;
    if(partitions->partitionMap[2] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[3] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[4] != 2) return 1 ;
    if(partitions->partitionMap[5] != 3) return 1 ;
    if(partitions->partitionMap[6] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[7] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[8] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[9] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[10] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[11] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[12] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[13] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[14] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[15] != ULONG_MAX) return 1 ;

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

    metaTspInstance = generate_meta_instance(instance, max_derivation_function_saving) ;

    if(metaTspInstance->end->nodes != 2) return 1 ;

    costs = metaTspInstance->end->costs ;

    if(costs[0] != 0) return 1;
    if(costs[1] != 60) return 1;
    if(costs[2] != 20) return 1;
    if(costs[3] != 0) return 1;

    partitions = metaTspInstance->partitions ;

    if(partitions->partitions != 2) return 1 ;

    if(partitions->partitionMap[0] != 0) return 1 ;
    if(partitions->partitionMap[1] != 1) return 1 ;
    if(partitions->partitionMap[2] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[3] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[4] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[5] != 2) return 1 ;
    if(partitions->partitionMap[6] != 3) return 1 ;
    if(partitions->partitionMap[7] != 4) return 1 ;
    if(partitions->partitionMap[8] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[9] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[10] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[11] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[12] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[13] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[14] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[15] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[16] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[17] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[18] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[19] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[20] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[21] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[22] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[23] != ULONG_MAX) return 1 ;
    if(partitions->partitionMap[24] != ULONG_MAX) return 1 ;

    destroy_meta_instance(metaTspInstance) ;

    return 0 ;
}