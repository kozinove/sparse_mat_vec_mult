#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mkl_pardiso.h"
#include "mkl_types.h"
#include "mkl_spblas.h"
#include <string.h>

#include "MatMV.h"

void stat(int n, int* RowIndex, int* ColIndex)
{
  int min_elem=1000000;
  int max_elem=0;
  
  double avg = (double)RowIndex[n] / (double)n;
  double q = 0.0;
  
  for(int i = 0; i < n; i++)
  {
    int s = RowIndex[i];
    int f = RowIndex[i+1];
    int d = f - s; 
    if(min_elem > d) min_elem = d; 
    if(max_elem < d) max_elem = d; 
    q += (avg - d) * (avg - d);
  }
  
  q /= n;
  q = sqrt(q);
  
  printf("min_elem : %d\n", min_elem);
  printf("max_elem : %d\n", max_elem);
  printf("avg : %lf\n", avg);
  printf("q : %lf\n", q);
}

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