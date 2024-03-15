#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/model/model.h"
#include "solvers/highsSolver.h"


int size = 10 ;

long costs[] = {0,5,-6,0,-8,-7,9,-8,6,-8,
        0,0,-1,7,1,-1,-3,-6,-8,7,
        7,7,0,-6,-3,0,8,-6,-9,-1,
        -5,3,0,0,-6,4,-2,-6,-9,6,
        -4,-2,-1,6,0,8,-6,5,-5,9,
        -6,3,-3,-5,9,0,-6,-4,8,-9,
        -8,0,-5,-7,0,-3,0,0,0,-3,
        5,6,-6,1,-7,8,-3,0,-5,-4,
        0,5,-8,3,-1,7,0,4,0,8,
        2,3,5,-9,2,-1,-8,4,-5,0} ;

int main() 
{
    printf("Seeing if the format is correct\n") ;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%ld,", costs[i*size + j]) ;
        }
        printf("\n") ;
    }

    struct TSP_instance *instance = create_instance(size, costs) ;

    TSP_heuristic_algorithm(instance, min_derivation_function_minRec,
        min_reconstruction_function, highs_solver, 2) ;

    int result = 0 ;

    if(check_instance_is_correct(instance) != 0) result = 1 ;
    if(check_instance_connection(instance) != 0) result = 1 ;

    puts("") ;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d ", instance->adjacencies[i*size + j]) ;
        }
        puts("") ;
    }

    if(get_nodes_adjacency(instance, 0, 7) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 7, 4) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 4, 1) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 1, 8) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 8, 2) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 2, 3) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 3, 6) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 6, 5) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 5, 9) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 9, 0) == 0) result = 1 ;

    destroy_instance(instance) ;

    instance = create_instance(size, costs) ;

    TSP_heuristic_algorithm(instance, min_derivation_function_saving,
        saving_reconstruction_function, highs_solver, 2) ;

    if(check_instance_is_correct(instance) != 0) result = 1 ;
    if(check_instance_connection(instance) != 0) result = 1 ;

    puts("") ;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d ", instance->adjacencies[i*size + j]) ;
        }
        puts("") ;
    }

    if(get_nodes_adjacency(instance, 0, 5) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 5, 9) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 9, 6) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 6, 1) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 1, 7) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 7, 4) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 4, 8) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 8, 2) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 2, 3) == 0) result = 1 ;
    if(get_nodes_adjacency(instance, 3, 0) == 0) result = 1 ;

    destroy_instance(instance) ;
    return result ;
}
