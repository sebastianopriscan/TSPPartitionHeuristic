#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    if(argc != 3) {
        fprintf(stderr, "Usage: ./exName size filename\n") ;
        exit(1) ;
    }

    FILE *output ;

    if((output = fopen(argv[2], "w+")) == NULL) {
        perror("Error opening file: ") ;
        exit(1) ;
    }

    int size = strtol(argv[1], NULL, 10) ;

    int *costMat ;

    if((costMat = malloc(sizeof(int)*size*size)) == NULL) {
        perror("Error allocating costMat.") ;
        exit(1) ;
    }

    memset(costMat, 0, sizeof(int)*size*size) ;

    int a = 1, b = 1 ;

    fprintf(output, "param m := %d ; #Numero di vincoli\n", 2*size) ;
    fprintf(output, "\nparam n := %d ; #Numero di variabili\n", size*size - size) ;
    fputs("\n", output) ;
    fprintf(output, "param A := ") ;

    while(a <= 2*size) {
        int var = (a +1) / 2, in_out = (a-1) % 2 ;

        for (int i = 1; i <= size; i++) {
            for(int j = 1; j <= size; j++) {
                if(i != j) {
                    if(a != 1 || b != 1)
                        fprintf(output, "           ") ;

                    if(in_out == 0) {
                        if(var == i)
                            fprintf(output, "%d %d 1\n", a, b) ;
                        else
                            fprintf(output, "%d %d 0\n", a, b) ;
                    }
                    else {
                        if(var == j)
                            fprintf(output, "%d %d 1\n", a, b) ;
                        else
                            fprintf(output, "%d %d 0\n", a, b) ;
                    }
                    b++ ;
                }
            }
        }
        b = 1 ;
        a++ ;
    }

    fseek(output, -1, SEEK_CUR) ;
    fputs(" ;\n", output) ;
    fprintf(output, "\nparam b := ") ;

    for(int i = 1 ; i <= 2*size ; i++) {
        if(i != 1)
            fprintf(output, "           %d 1\n", i) ;
        else
            fprintf(output, "%d 1\n", i) ;
    }

    fseek(output, -1, SEEK_CUR) ;
    fputs(" ;\n", output) ;
    fprintf(output, "\nparam C := ") ;


    srand(4567) ;
    a = 1;
    for (int i = 1; i <= size; i++) {
        for(int j = 1; j <= size; j++) {
            if(i != j) {
                int number = rand() % 10 ;
                int sign = rand() > RAND_MAX/2 ? 1 : -1 ;
                number = number * sign ;
                costMat[(i-1)*size +j-1] = number ;
                if(a == 1) {
                    fprintf(output, "%d %d\n", a, number) ;
                } else {
                    fprintf(output, "           %d %d\n", a, number) ;
                }
                a++ ;
            }
        }
    }

    fseek(output, -1, SEEK_CUR) ;
    fputs(" ;", output) ;

    printf(" ;") ;
    for(int i = 1; i <= size; i++) {
        printf("%d;", i) ;
    }
    puts("");
    a=1 ;
    while(a <= size) {

        printf("%d;", a) ;
        for(int i = 1; i <= size; i++) {
            printf("%d;", costMat[(a-1)*size + i-1]) ;
        }
        puts("") ;
        a++;
    }

    return 0 ;
}