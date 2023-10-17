#include "interfaces/highs_c_api.h"

#include <stdlib.h>

int main(void)
{
    //Let's try to solve a Knapsack problem

    int numCol = 4 ;
    int numRow = 1 ;
    int numNz = 4 ;

    int sense = kHighsObjSenseMaximize ;
    const double offset = 0 ;

    const double col_cost[4] = {3.0, 4.0, 1.4, 6.0} ;
    const double col_lower[4] = {0.0, 0.0, 0.0, 0.0} ;
    const double col_upper[4] = {1.0, 1.0, 1.0, 1.0} ;

    const double row_lower[1] = {0.0} ;
    const double row_upper[1] = {5.0} ;

    const int a_format = kHighsMatrixFormatColwise ;

    const int a_start[4] = {0, 1, 2, 3} ;
    const int a_index[4] = {0, 0, 0, 0} ;
    const double a_value[4] = {1.5, 3.0, 2.0, 4.0} ;

    const int integralities[4] = {kHighsVarTypeInteger, kHighsVarTypeInteger, kHighsVarTypeInteger, kHighsVarTypeInteger} ;

    double objective_value;
    double* col_value = (double*)malloc(sizeof(double) * numCol);
    double* row_value = (double*)malloc(sizeof(double) * numRow);

    int model_status;
    int run_status;

    run_status = Highs_mipCall(numCol, numRow, numNz, a_format,
                              sense, offset, col_cost, col_lower, col_upper, row_lower, row_upper,
                              a_start, a_index, a_value, integralities,
                              col_value, row_value,
                              &model_status);

    if(run_status != kHighsStatusOk) return 1 ;
    if(model_status != kHighsModelStatusOptimal) return 1 ;

    objective_value = offset;
    for (int i = 0; i < numCol; i++) {
        objective_value += col_value[i]*col_cost[i];
    }

    if(objective_value != 7) return 1 ;

    return 0 ;
}