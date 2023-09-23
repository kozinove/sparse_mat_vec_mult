#ifndef __SOLVE_SYSTEM_MKL_
#define __SOLVE_SYSTEM_MKL_

#include "readFile.h"
#include "omp.h"

void toOneBase(int n, int* RowIndex, int* ColIndex);
void MatMV(int n, int* col, int* row, FLOAT_TYPE* val, FLOAT_TYPE* x, FLOAT_TYPE* res);


void GenerateSolution(int* col, int* row, FLOAT_TYPE* val,  
                      FLOAT_TYPE* x, FLOAT_TYPE* b, int n);
						  
void toZeroBase(int n, int* RowIndex, int* ColIndex);

void stat(int n, int* RowIndex, int* ColIndex);

FLOAT_TYPE CheckError(int n, int* col, int* row, FLOAT_TYPE* val, FLOAT_TYPE* b, FLOAT_TYPE* x);

#endif