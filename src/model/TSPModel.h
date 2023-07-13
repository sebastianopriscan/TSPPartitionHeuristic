#ifndef MODEL_H
#error 'This file should not be included directly'
#endif

struct TSP_instance {
    unsigned long nodes ;
    long *costs ;
    unsigned char *adjacencies ;
};

struct partitions {
    unsigned long nodes ;
    unsigned long partitions ;
    unsigned char partitionMap[] ;
};

struct meta_TSP_instance {
    struct TSP_instance *start ;
    struct partitions *partitions ;
    struct TSP_instance *end ;
};

extern struct TSP_instance *create_instance(unsigned long nodes, long *costs) ;
extern long get_connection_cost(struct TSP_instance *instance, unsigned long from, unsigned long to) ;
extern unsigned char get_nodes_adjacency(struct TSP_instance *instance, unsigned long node1, unsigned long node2) ;

extern unsigned char check_instance_is_correct(struct TSP_instance *instance) ;
extern unsigned char check_instance_connection(struct TSP_instance *instance) ;
extern struct meta_TSP_instance *generate_meta_instance(struct TSP_instance *instance,
        long *distance_derivation_function(struct TSP_instance *, struct partitions *)) ;

extern void destroy_instance(struct TSP_instance *instance) ;
extern void destroy_meta_instance(struct meta_TSP_instance *metaTspInstance) ;