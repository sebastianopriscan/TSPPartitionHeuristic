#include "model.h"

struct TSP_instance *create_instance(unsigned long nodes, long *costs)
{
    struct TSP_instance *retVal ;
    if((retVal = malloc(sizeof(struct TSP_instance))) == NULL)
    {
        perror("Error in allocating memory for new TSP instance: ") ;
        exit(1) ;
    }

    retVal->nodes = nodes ;
    retVal->costs = costs ;

    unsigned char *adjTable ;
    if((adjTable = malloc(sizeof(unsigned char) * nodes * nodes)) == NULL)
    {
        perror("Error in allocating memory for new TSP instance adj table: ") ;
        exit(1) ;
    }

    unsigned int i = 0 ;
    while (i < nodes * nodes) {
        adjTable[i] = 0 ;
        i++ ;
    }

    retVal->adjacencies = adjTable ;

    return retVal ;
}

long get_connection_cost(struct TSP_instance *instance, unsigned long from, unsigned long to)
{
    return instance->costs[instance->nodes * from + to] ;
}

unsigned char get_nodes_adjacency(struct TSP_instance *instance, unsigned long node1, unsigned long node2)
{
    return instance->adjacencies[instance->nodes * node1 + node2] ;
}

unsigned char check_instance_is_correct(struct TSP_instance *instance)
{
    unsigned char colCount[instance->nodes] ;

    unsigned int i = 0 ;
    while (i < instance->nodes)
    {
        colCount[i] = 0 ;
        i++ ;
    }

    for (i = 0 ; i < instance->nodes ; i++)
    {
        int count = 0 ;
        for (unsigned int j = 0; j < instance->nodes; j++) {
            if(instance->adjacencies[i * instance->nodes + j] == 1)
            {
                count++ ;
                if(colCount[j] == 1) return 1 ;
                else colCount[j]++ ;
            }
            if(instance->adjacencies[i * instance->nodes + j] != 0 && instance->adjacencies[i * instance->nodes + j] != 1)
                return 1 ;
        }
        if(count != 1) return 1 ;
    }

    return 0 ;
}

unsigned char check_instance_connection(struct TSP_instance *instance)
{
    unsigned char nodeFlags[instance->nodes] ;
    unsigned int i = 1 ;
    nodeFlags[0] = 1 ;
    while (i < instance->nodes)
    {
        nodeFlags[i] = 0 ;
        i++ ;
    }

    unsigned char *adjTable = instance->adjacencies ;

    i = 0 ;

SEARCH_LOOP :
    for (unsigned int j = 0 ; j < instance->nodes ; j++)
    {
        if(adjTable[i * instance->nodes + j] != 0)
        {
            if(nodeFlags[j] == 1) break ;
            nodeFlags[j] = 1 ;
            i = j ;
            goto SEARCH_LOOP;
        }
    }

    i = 0 ;
    while (i < instance->nodes)
    {
        if (nodeFlags[i] == 0) return 1;
        i++ ;
    }

    return 0 ;
}

static inline struct partitions *getPartitions(struct TSP_instance *instance)
{
    unsigned char nodeFlags[instance->nodes] ;
    unsigned int i = 1 ;
    nodeFlags[0] = 1 ;
    while (i < instance->nodes)
    {
        nodeFlags[i] = 0 ;
        i++ ;
    }

    struct partitions *retVal ;

    if((retVal = malloc(sizeof(struct partitions) + sizeof(unsigned char) * instance->nodes * instance->nodes)) == NULL)
    {
        perror("Unable to instantiate a partitions structure: ") ;
        exit(1) ;
    }

    retVal->nodes = instance->nodes ;
    retVal->partitions = 0 ;

    i = 0 ;
    while (i < retVal->nodes * retVal->nodes)
    {
        retVal->partitionMap[i] = 0 ;
        i++ ;
    }

    unsigned char *adjTable = instance->adjacencies ;

    retVal->partitions++ ;
    retVal->partitionMap[0] = 1 ;
    i = 0 ;

SEARCH_LOOP_2 :
    for (unsigned int j = 0 ; j < instance->nodes ; j++)
    {
        if(adjTable[i * instance->nodes + j] != 0)
        {
            if(nodeFlags[j] == 1) break ;
            retVal->partitionMap[(retVal->partitions -1) * retVal->nodes + j] = 1 ;
            nodeFlags[j] = 1 ;
            i = j ;
            goto SEARCH_LOOP_2;
        }
    }

    i = 0 ;
    while (i < instance->nodes)
    {
        if(nodeFlags[i] == 0)
        {
            retVal->partitions++ ;
            retVal->partitionMap[(retVal->partitions -1) * retVal->nodes +i] = 1 ;
            nodeFlags[i] = 1 ;
            goto SEARCH_LOOP_2 ;
        }
        i++ ;
    }

    return retVal ;
}


struct meta_TSP_instance *generate_meta_instance(struct TSP_instance *instance,
        long *distance_derivation_function(struct TSP_instance *, struct partitions *))
{
    if(check_instance_connection(instance) == 0) return NULL ;

    struct partitions *parts = getPartitions(instance) ;

    long *distances = distance_derivation_function(instance, parts) ;

    struct TSP_instance *end = create_instance(parts->partitions, distances) ;

    struct meta_TSP_instance *retVal ;

    if((retVal = malloc(sizeof(struct meta_TSP_instance))) == NULL)
    {
        perror("Unable to create meta instance: ") ;
        exit(1) ;
    }

    retVal->start = instance ;
    retVal->partitions = parts ;
    retVal->end = end ;

    return retVal ;
}

void destroy_instance(struct TSP_instance *instance)
{
    free(instance->adjacencies) ;
    free(instance) ;
}

void destroy_meta_instance(struct meta_TSP_instance *metaTspInstance)
{
    destroy_instance(metaTspInstance->start) ;
    destroy_instance(metaTspInstance->end) ;
    free(metaTspInstance->partitions) ;
    free(metaTspInstance) ;
}