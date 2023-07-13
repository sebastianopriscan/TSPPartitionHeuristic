#include "../src/model/model.h"

int main(void)
{
    long costsMat[4][4] = {{0, 10, 20, 30},
                           {30, 0, 60, 20},
                           {5, 20, 0, 50},
                           {1,1,1,0}} ;
    struct TSP_instance *testInstance = create_instance(4, (long *) costsMat) ;

    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            if(costsMat[i][j] != get_connection_cost(testInstance, i, j)) return 1 ;
        }
    }

    return 0 ;
}