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
    *(adjacencies + 4 + 2) = 1 ;
    *(adjacencies + 8 + 3) = 1 ;
    *(adjacencies + 12) = 1 ;

    if(check_instance_connection(instance) != 0) return 1 ;

    *(adjacencies + 4 + 2) = 0 ;
    *(adjacencies + 4) = 1 ;

    *(adjacencies + 12) = 0 ;
    *(adjacencies + 12 + 2) = 1 ;

    if(check_instance_connection(instance) != 1) return 1 ;

    return 0 ;
}