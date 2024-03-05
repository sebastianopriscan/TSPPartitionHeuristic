#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../src/model/model.h"
#include "solvers/highsSolver.h"

DIR *directory ;
struct dirent *directory_struct ;
FILE *file ;

char nameBuffer[4096] ;
char *position ;

int derivation_functions_types = 3, reconstruction_functions_types = 2 ;

long *(*(derivation_functions[2][3]))(struct TSP_instance *, struct partitions *) = {{min_derivation_function_minRec,
                                                                                      max_derivation_function_minRec,
                                                                                      average_derivation_function_minRec},
                                                                                     {min_derivation_function_saving,
                                                                                      max_derivation_function_saving,
                                                                                      average_derivation_function_saving}} ;

void (*(reconstruction_functions[2]))(struct meta_TSP_instance *) = {min_reconstruction_function,
                                                                    saving_reconstruction_function
                                                                   } ;



char lineBuffer[4096] ;

int failure = 0;

int main(void)
{
    position = stpcpy(nameBuffer, "../../test/resources/") ;
    if((directory = opendir("../../test/resources")) == NULL)
    {
        perror("Error in opening resources dir, Exiting...") ;
        exit(1) ;
    }

    while ((directory_struct = readdir(directory)) != NULL)
    {
        if(strcmp(directory_struct->d_name, ".") == 0|| strcmp(directory_struct->d_name, "..") == 0)
            continue;

        strcpy(position, directory_struct->d_name) ;
        if((file = fopen(nameBuffer, "r")) == NULL)
        {

            fprintf(stderr, "Error opening file %s ", nameBuffer) ;
            perror("") ;
            exit(1) ;
        }

        int numberOfInstances, instanceSize ;

        fgets(lineBuffer, 4096, file) ;

        char *token = strtok(lineBuffer, " ") ;

        if(token == NULL)
        {
            fprintf(stderr, "Wrong string format") ;
            exit(1) ;
        }

        char *nptr ;

        numberOfInstances = (int) strtol(token, &nptr, 10) ;

        if(*nptr != '\0' || nptr == token)
        {
            perror("Wrong string format") ;
            exit(1) ;
        }

        token = strtok(NULL, "\n") ;
        instanceSize = (int) strtol(token, &nptr, 10) ;

        if(*nptr != '\0' || nptr == token)
        {
            perror("Wrong string format") ;
            exit(1) ;
        }

        for (int i = 0; i < numberOfInstances; i++)
        {
            long *costMatrix ;

            if((costMatrix = malloc(sizeof (long) * instanceSize * instanceSize)) == NULL)
            {
                perror("Error allocating instance memory") ;
                exit(1) ;
            }

            fgets(lineBuffer, 4096, file) ;

            for (int j = 0; j < instanceSize ; j++)
            {
                token = strtok(lineBuffer, " ") ;

                for (int q = 0; q < instanceSize ; q++)
                {
                    if(token == NULL)
                    {
                        perror("Wrong string format") ;
                    }

                    costMatrix[j * instanceSize + q] = strtol(token, &nptr, 10) ;

                    token = strtok(NULL, " ") ;
                }

                fgets(lineBuffer, 4096, file) ;
            }

            for (int j = 0 ; j < reconstruction_functions_types ; j++)
                for (int q = 0 ; q < derivation_functions_types ; q++)
                {
                    struct TSP_instance *instance = create_instance(instanceSize, costMatrix) ;

                    TSP_heuristic_algorithm(instance, derivation_functions[j][q], reconstruction_functions[j], highs_solver, 2) ;
                    if(check_instance_is_correct(instance) != 0 || check_instance_connection(instance) != 0)
                    {
                        printf("Instance %d of file %s is not correct with policy combo %d,%d\n", i, nameBuffer, j, q) ;
                        failure = 1 ;
                    }

                    destroy_instance(instance) ;
                }

            free(costMatrix) ;
        }
    }

    return failure ;
}