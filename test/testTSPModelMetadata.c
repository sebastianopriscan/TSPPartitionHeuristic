#include "../src/model/model.h"

int main(void)
{
    struct TSP_instance *instance ;

    unsigned char *adjacencies ;

    struct meta_TSP_instance *metaTspInstance ;

    struct partitions *partitions ;

    long fiveCostMat[5][5] = {{0, 10, 20, 30, 40},
                              {30, 0, 60, 20, 34},
                              {5, 20, 0, 50, 66},
                              {1,1,1,0, -4},
                              {4,7,5,-2,1}} ;


    void *functions[3] = {min_derivation_function_minRec, max_derivation_function_minRec, average_derivation_function_minRec} ;

    for (int i = 0; i < 3; i++)
    {
        instance = create_instance(5, (long *)fiveCostMat) ;

        adjacencies = instance->adjacencies ;

        *(adjacencies + 1) = 1 ;
        *(adjacencies + 5) = 1 ;
        *(adjacencies + 10 + 3) = 1 ;
        *(adjacencies + 15 + 4) = 1 ;
        *(adjacencies + 20 + 2) = 1 ;

        metaTspInstance = generate_meta_instance(instance, functions[i]) ;

        partitions = metaTspInstance->partitions ;

        struct partition_indexes *indexes = (struct partition_indexes *)partitions->metadata ;

        if(indexes[0].entranceIndex != ULONG_MAX || indexes[0].exitIndex != ULONG_MAX) return 1 ;
        if(indexes[1].entranceIndex != 0 || indexes[1].exitIndex != 0) return 1 ;
        if(indexes[2].entranceIndex != 0 || indexes[2].exitIndex != 1) return 1 ;
        if(indexes[3].entranceIndex != ULONG_MAX || indexes[3].exitIndex != ULONG_MAX) return 1 ;

        if(partitions->partitionMap[indexes[1].entranceIndex] != 0 || partitions->partitionMap[indexes[1].exitIndex] != 0) return 1 ;
        if(partitions->partitionMap[5 + indexes[2].entranceIndex] != 2 || partitions->partitionMap[5 +indexes[2].exitIndex] != 3) return 1 ;

        destroy_meta_instance(metaTspInstance) ;
    }

    return 0 ;
}