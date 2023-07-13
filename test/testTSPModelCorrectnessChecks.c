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

    if(check_instance_is_correct(instance) != 0) return 1 ;

    *(adjacencies + 12) = 0 ;
    *(adjacencies + 12 + 1) = 1 ;

    if(check_instance_is_correct(instance) != 1) return 1 ;

    *(adjacencies + 12) = 1 ;
    *(adjacencies + 12 + 1) = 0 ;

    *(adjacencies + 3) = 2 ;

    if(check_instance_is_correct(instance) != 1) return 1 ;

    *(adjacencies + 3) = 0 ;
    *(adjacencies + 9) = 2 ;

    if(check_instance_is_correct(instance) != 1) return 1 ;

    *(adjacencies + 9) = 0 ;
    *(adjacencies + 14) = -1 ;

    if(check_instance_is_correct(instance) != 1) return 1 ;

    *(adjacencies + 3) = 2 ;
    *(adjacencies + 9) = 2 ;

    if(check_instance_is_correct(instance) != 1) return 1 ;


}