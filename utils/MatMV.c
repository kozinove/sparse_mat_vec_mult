#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mkl_pardiso.h"
#include "mkl_types.h"
#include "mkl_spblas.h"
#include <string.h>

#include "MatMV.h"

//typedef std::chrono::high_resolution_clock Clock;

void toOneBase(int n, int* RowIndex, int* ColIndex)
{
	int i;
  for (i = 0; i < RowIndex[n]; i++)
  {
    ColIndex[i]++;
  }

  for (i = 0; i <= n; i++)
  {
    RowIndex[i]++;
  }
}
void toZeroBase(int n, int* RowIndex, int* ColIndex)
{
  int i;
  for (i = 0; i <= n; i++)
  {
    RowIndex[i]--;
  }
  for (i = 0; i < RowIndex[n]; i++)
  {
    ColIndex[i]--;
  }
}

void ToOneBasedNumbering(int* arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
		arr[i]++;
}