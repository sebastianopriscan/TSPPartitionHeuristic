#include "sampler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#define _CLEAN_ENTRY(SYM, EXTRA) while(state.SYM != NULL) {\
        struct node *next = state.SYM->next ;\
        EXTRA \
        free(state.SYM->data) ;\
        free(state.SYM) ;\
        state.SYM = next ;\
    }\

#define CLEAN_ENTRY_SIMPLE(SYM) _CLEAN_ENTRY(SYM,)
#define CLEAN_ENTRY(SYM) CLEAN_ENTRY_SIMPLE(SYM) \
    state.SYM##_end = NULL ;\


#define CLEAN_DATA_ENTRY_SIMPLE(SYM) _CLEAN_ENTRY(SYM, free(((struct pointer_content *)state.SYM->data)->data);)
#define CLEAN_DATA_ENTRY(SYM) CLEAN_DATA_ENTRY_SIMPLE(SYM)  \
    state.SYM##_end = NULL ;\

#define PRINT_LOOP(VAR, TYPE, FORMAT, STREAM) {struct pointer_content *content = (struct pointer_content *)VAR->data ;\
        for(int j = 0 ; j < content->size ; j++) {\
            for(int q = 0 ; q < content->size ; q++) {\
                fprintf(STREAM, FORMAT "; ", ((TYPE *)content->data)[j*content->size + q]) ;\
            }\
            fprintf(STREAM, "\n") ;\
        }}\

#define OPEN_DESCPRIPTOR(FILE_DESC, MACRO_NAME)\
        if(FILE_DESC == NULL) {\
            if((FILE_DESC = fdopen(MACRO_NAME, "w")) == NULL)\
            {\
                perror("Error opening descriptor. Exiting...");\
                exit(1);\
            }\
        }\

struct node
{
    void *data ;
    struct node *next ;
} ;

struct long_container
{
    long content ;
} ;

struct pointer_content {
    void *data;
    long size ;
} ;

struct sampler_state
{
    int recursion_steps ;

    struct node *in_solver_times ;
    struct node *in_solver_times_end ;

    struct node *in_derivation_times ;
    struct node *in_derivation_times_end ;

    struct node *in_reconstruction_times ;

    struct node *costs ;
    struct node *costs_end ;

    struct node *adjacencies ;

    struct node *partitions ;
    struct node *partitions_end ;
} ;

static FILE *selected_codes[4] = {NULL, NULL, NULL, NULL} ; 
static struct sampler_state state ;

static FILE *costs_output = NULL ;
static FILE *times_output = NULL ;
static FILE *adjacencies_output = NULL ;
static FILE *partitions_output = NULL ;

void increaseRecursiveSteps()
{
    state.recursion_steps++ ;
}

void registerTimeSpentInSolver(long time)
{
    struct node *nodeToSave ;
    struct long_container *container ;

    if((nodeToSave = malloc(sizeof(struct node))) == NULL) {
        perror("Error allocating node memory") ;
        return ;
    }

    if((container = malloc(sizeof(struct long_container))) == NULL) {
        perror("Error allocating container memory") ;
        free(nodeToSave) ;
        return ;
    }
    container->content = time ;
    nodeToSave->data = container ;
    nodeToSave->next = NULL ;

    if(state.in_solver_times_end == NULL)
        state.in_solver_times = state.in_solver_times_end = nodeToSave ;
    else {
        state.in_solver_times_end->next = nodeToSave ;
        state.in_solver_times_end = nodeToSave ;
    }
}

void registerTimeSpentInDerivation(long time)
{
    struct node *nodeToSave ;
    struct long_container *container ;

    if((nodeToSave = malloc(sizeof(struct node))) == NULL) {
        perror("Error allocating node memory") ;
        return ;
    }

    if((container = malloc(sizeof(struct long_container))) == NULL) {
        perror("Error allocating container memory") ;
        free(nodeToSave) ;
        return ;
    }
    container->content = time ;
    nodeToSave->data = container ;
    nodeToSave->next = NULL ;

    if(state.in_derivation_times_end == NULL)
        state.in_derivation_times = state.in_derivation_times_end = nodeToSave ;
    else {
        state.in_derivation_times_end->next = nodeToSave ;
        state.in_derivation_times_end = nodeToSave ;
    }
}

void registerTimeSpentInReconstruction(long time)
{
    struct node *nodeToSave ;
    struct long_container *container ;

    if((nodeToSave = malloc(sizeof(struct node))) == NULL) {
        perror("Error allocating node memory") ;
        return ;
    }

    if((container = malloc(sizeof(struct long_container))) == NULL) {
        perror("Error allocating container memory") ;
        free(nodeToSave) ;
        return ;
    }
    container->content = time ;
    nodeToSave->data = container ;
    nodeToSave->next = NULL ;

    if(state.in_reconstruction_times == NULL)
        state.in_reconstruction_times = nodeToSave ;
    else {
        nodeToSave->next = state.in_reconstruction_times ;
        state.in_reconstruction_times = nodeToSave ;
    }
}

void registerInstanceCosts(long *costs, long size)
{
    struct node *nodeToSave ;
    struct pointer_content *content;
    void *data ;

    if((nodeToSave = malloc(sizeof(struct node))) == NULL) {
        perror("Error allocating node memory") ;
        return ;
    }

    if((content = malloc(sizeof(struct pointer_content))) == NULL) {
        perror("Error allocating content memory") ;
        free(nodeToSave) ;
        return ;
    }

    if((data = malloc(size * size * sizeof(long))) == NULL) {
        perror("Error allocating container memory") ;
        free(nodeToSave) ;
        free(content) ;
        return ;
    }
    memcpy(data, costs, size * size * sizeof(long)) ;
    content->data = data ;
    content->size = size ;
    nodeToSave->data = content ;
    nodeToSave->next = NULL ;

    if(state.costs_end == NULL)
        state.costs = state.costs_end = nodeToSave ;
    else {
        state.costs_end->next = nodeToSave ;
        state.costs_end = nodeToSave ;
    }
}

void registerInstanceAdjacencies(unsigned char *adjacencies, long size)
{
    struct node *nodeToSave ;
    struct pointer_content *content;
    void *data ;

    if((nodeToSave = malloc(sizeof(struct node))) == NULL) {
        perror("Error allocating node memory") ;
        return ;
    }

    if((content = malloc(sizeof(struct pointer_content))) == NULL) {
        perror("Error allocating content memory") ;
        free(nodeToSave) ;
        return ;
    }

    if((data = malloc(size * size * sizeof(unsigned char))) == NULL) {
        perror("Error allocating container memory") ;
        free(nodeToSave) ;
        free(content) ;
        return ;
    }
    memcpy(data, adjacencies, size * size * sizeof(unsigned char)) ;
    content->data = data ;
    content->size = size ;
    nodeToSave->data = content ;
    nodeToSave->next = NULL ;

    if(state.adjacencies == NULL)
        state.adjacencies = nodeToSave ;
    else {
        nodeToSave->next = state.adjacencies ;
        state.adjacencies = nodeToSave ;
    }
}

void registerPartitions(unsigned long *partitionMap, long size)
{
    struct node *nodeToSave ;
    struct pointer_content *content;
    void *data ;

    if((nodeToSave = malloc(sizeof(struct node))) == NULL) {
        perror("Error allocating node memory") ;
        return ;
    }

    if((content = malloc(sizeof(struct pointer_content))) == NULL) {
        perror("Error allocating content memory") ;
        free(nodeToSave) ;
        return ;
    }

    if((data = malloc(size * size * sizeof(unsigned long))) == NULL) {
        perror("Error allocating container memory") ;
        free(nodeToSave) ;
        free(content) ;
        return ;
    }
    memcpy(data, partitionMap, size * size * sizeof(unsigned long)) ;
    content->data = data ;
    content->size = size ;
    nodeToSave->data = content ;
    nodeToSave->next = NULL ;

    if(state.partitions_end == NULL)
        state.partitions = state.partitions_end = nodeToSave ;
    else {
        state.partitions_end->next = nodeToSave ;
        state.partitions_end = nodeToSave ;
    }
}

void resetState()
{
    state.recursion_steps = 0 ;

    CLEAN_ENTRY(in_solver_times)

    CLEAN_ENTRY(in_derivation_times)

    CLEAN_ENTRY_SIMPLE(in_reconstruction_times)

    CLEAN_DATA_ENTRY(costs)
    
    CLEAN_DATA_ENTRY_SIMPLE(adjacencies)

    CLEAN_DATA_ENTRY(partitions)
    
    int j = 1 ;
    OPEN_DESCPRIPTOR(costs_output, COSTS_OUTPUT_DESC)
    selected_codes[0] = costs_output ;

    if(TIMES_OUTPUT_DESC == COSTS_OUTPUT_DESC) {
        times_output = costs_output ;
    } else {
        OPEN_DESCPRIPTOR(times_output, TIMES_OUTPUT_DESC)
        selected_codes[j] = times_output ;
        j++ ;
    }

    if(ADJACENCIES_OUTPUT_DESC == COSTS_OUTPUT_DESC) {
        adjacencies_output = costs_output ;
    } else if (ADJACENCIES_OUTPUT_DESC == TIMES_OUTPUT_DESC) {
        adjacencies_output = times_output ;
    } else {
        OPEN_DESCPRIPTOR(adjacencies_output, ADJACENCIES_OUTPUT_DESC)
        selected_codes[j] = adjacencies_output ;
        j++ ;
    }

    if(PARTITIONS_OUTPUT_DESC == COSTS_OUTPUT_DESC) {
        partitions_output = costs_output ;
    } else if(PARTITIONS_OUTPUT_DESC == TIMES_OUTPUT_DESC) {
        partitions_output = times_output ;
    } else if(PARTITIONS_OUTPUT_DESC == ADJACENCIES_OUTPUT_DESC) {
        partitions_output = adjacencies_output ;
    } else {
        OPEN_DESCPRIPTOR(partitions_output, PARTITIONS_OUTPUT_DESC)
        selected_codes[j] = partitions_output ;
    }
} 


void printState() 
{
    struct node * current_solver = state.in_solver_times, 
                * current_derivation = state.in_derivation_times,
                * current_reconstruction = state.in_reconstruction_times,
                * current_cost = state.costs,
                * current_adjacencies = state.adjacencies,
                * current_partitions = state.partitions ;

    for(int i = 0; i < state.recursion_steps; i++) {

        for(int k = 0; k < 4; k++) {
            if(selected_codes[k] == NULL) break ;
            fprintf(selected_codes[k], "Recursion step %d:\n", i) ;
        }
        printf("Recursion step %d:\n", i) ;

        fprintf(times_output,"Time_solving ; Time_derivating ; Time_reconstructing\n") ;
        fprintf(times_output,"%ld ; %ld ; %ld\n",
            ((struct long_container *)(current_solver->data))->content,
            current_derivation != NULL ? ((struct long_container *)(current_derivation->data))->content : 0,
            current_reconstruction != NULL ? ((struct long_container *)(current_reconstruction->data))->content : 0) ;

        fprintf(costs_output, "Costs:\n") ;
        PRINT_LOOP(current_cost, long, "%ld", costs_output)
        fprintf(adjacencies_output,"Adjacencies:\n") ;
        PRINT_LOOP(current_adjacencies, unsigned char, "%d", adjacencies_output)

        if(current_partitions != NULL) {
            fprintf(partitions_output, "Partitions:\n") ;
            struct pointer_content *content = (struct pointer_content *)current_partitions->data ;
            for(int j = 0 ; j < content->size ; j++) {
                if(((unsigned long *)content->data)[j*content->size] == ULONG_MAX) break ;
                for(int q = 0 ; q < content->size ; q++) {
                    if(((unsigned long *)content->data)[j*content->size + q] == ULONG_MAX) break ;
                    fprintf(partitions_output, "%ld; ", ((unsigned long*)content->data)[j*content->size + q]) ;
                }
                fprintf(partitions_output, "\n") ;
            }
        }

        current_solver = current_solver->next ;
        current_derivation = current_derivation != NULL ? current_derivation->next : NULL ; 
        current_reconstruction = current_reconstruction != NULL ? current_reconstruction->next : NULL ; 
        current_cost = current_cost->next ; 
        current_adjacencies = current_adjacencies->next ; 
        current_partitions = current_partitions != NULL ? current_partitions->next : NULL ; 
    }
}
