#include "../src/model/model.h"

int main(void)
{
    long costsMat[4][4] = {{0, 10, 20, 30},
                           {30, 0, 60, 20},
                           {5, 20, 0, 50},
                           {20,1,1,0}} ;

    struct TSP_instance *instance = create_instance(4, (long *)costsMat) ;

    unsigned char *adjacencies = instance->adjacencies ;

    *(adjacencies + 1) = 1 ;
    *(adjacencies + 4) = 1 ;
    *(adjacencies + 8 + 3) = 1 ;
    *(adjacencies + 12 + 2) = 1 ;

    struct meta_TSP_instance *metaTspInstance = generate_meta_instance(instance, min_derivation_function_minRec) ;

    metaTspInstance->end->adjacencies[0] = 0 ;
    metaTspInstance->end->adjacencies[1] = 1 ;
    metaTspInstance->end->adjacencies[2] = 1 ;
    metaTspInstance->end->adjacencies[3] = 0 ;

    min_reconstruction_function(metaTspInstance) ;

    if(check_instance_is_correct(instance) != 0) return 1 ;
    if(check_instance_connection(instance) != 0) return 1 ;


    destroy_meta_instance(metaTspInstance) ;

    long fiveCostMat[5][5] = {{0, 10, 20, 30, 40},
                              {30, 0, 60, 20, 34},
                              {5, 20, 0, 50, 66},
                              {10,1,1,0, -4},
                              {4,7,5,-2,1}} ;

    instance = create_instance(5, (long *)fiveCostMat) ;

    adjacencies = instance->adjacencies ;

    *(adjacencies + 1) = 1 ;
    *(adjacencies + 5) = 1 ;
    *(adjacencies + 10 + 3) = 1 ;
    *(adjacencies + 15 + 4) = 1 ;
    *(adjacencies + 20 + 2) = 1 ;

    metaTspInstance = generate_meta_instance(instance, min_derivation_function_minRec) ;

    metaTspInstance->end->adjacencies[0] = 0 ;
    metaTspInstance->end->adjacencies[1] = 1 ;
    metaTspInstance->end->adjacencies[2] = 1 ;
    metaTspInstance->end->adjacencies[3] = 0 ;

    min_reconstruction_function(metaTspInstance) ;

    if(check_instance_is_correct(instance) != 0) return 1 ;
    if(check_instance_connection(instance) != 0) return 1 ;

    destroy_meta_instance(metaTspInstance) ;

    long costsMat2[5][5] = {{0, 10, 20, 30, 40},
                            {30, 0, 60, 20, 34},
                            {1, 20, 0, 50, 66},
                            {10,1,1,0, -4},
                            {4,7,5,-2,1}} ;

    instance = create_instance(5, (long *)costsMat2) ;

    adjacencies = instance->adjacencies ;

    *(adjacencies + 1) = 1 ;
    *(adjacencies + 5) = 1 ;
    *(adjacencies + 10 + 3) = 1 ;
    *(adjacencies + 15 + 4) = 1 ;
    *(adjacencies + 20 + 2) = 1 ;

    metaTspInstance = generate_meta_instance(instance, min_derivation_function_minRec) ;

    metaTspInstance->end->adjacencies[0] = 0 ;
    metaTspInstance->end->adjacencies[1] = 1 ;
    metaTspInstance->end->adjacencies[2] = 1 ;
    metaTspInstance->end->adjacencies[3] = 0 ;

    min_reconstruction_function(metaTspInstance) ;

    if(check_instance_is_correct(instance) != 0) return 1 ;
    if(check_instance_connection(instance) != 0) return 1 ;


    destroy_meta_instance(metaTspInstance) ;

    return 0 ;
}