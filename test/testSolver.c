#include "solvers/highsSolver.h"

int main(void)
{

    long costsMat[4][4] = {{0, 10, 20, 30},
                           {30, 0, 60, 20},
                           {5, 20, 0, 50},
                           {1,1,1,0}} ;

    struct TSP_instance *instance = create_instance(4, (long *)costsMat) ;

    highs_solver(instance, NOT_RELAXED) ;

    if(check_instance_connection(instance) != 0) return 1 ;
    if(check_instance_is_correct(instance) != 0) return 1 ;
    if(get_solution_cost(instance) != 36) return 1 ;

    destroy_instance(instance) ;

    long costsMat2[4][4] = {{0, 50, 1, 50},
                           {50, 0, 60, 20},
                           {-50, 50, 0, 50},
                           {100,-43,0,0}} ;

    instance = create_instance(4, (long *)costsMat2) ;

    highs_solver(instance, RELAXED) ;

    if(check_instance_connection(instance) == 0) return 1 ;
    if(check_instance_is_correct(instance) != 0) return 1 ;
    if(get_solution_cost(instance) != -72) return 1 ;

    return 0 ;
}