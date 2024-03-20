#define NORMAL_STREAM 1

#ifndef COSTS_OUTPUT_DESC
#define COSTS_OUTPUT_DESC NORMAL_STREAM
#endif
#ifndef TIMES_OUTPUT_DESC
#define TIMES_OUTPUT_DESC NORMAL_STREAM
#endif
#ifndef ADJACENCIES_OUTPUT_DESC
#define ADJACENCIES_OUTPUT_DESC NORMAL_STREAM
#endif
#ifndef PARTITIONS_OUTPUT_DESC
#define PARTITIONS_OUTPUT_DESC NORMAL_STREAM
#endif

void increaseRecursiveSteps() ;

void resetState() ;

void printState() ;

void registerTimeSpentInSolver(long time) ;

void registerTimeSpentInDerivation(long time) ;

void registerTimeSpentInReconstruction(long time) ;

void registerInstanceCosts(long *costs, long size) ;

void registerInstanceAdjacencies(unsigned char *adjacencies, long size) ;

void registerPartitions(unsigned long *partitionMap, long size) ;