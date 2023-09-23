#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "readFile.h"
#include "MatMV.h"
#include <omp.h>

#define FLOAT_TYPE double

// argv[1] - ���� � ��������
// argv[2] - ��� �������
int main(int argc, char **argv)
{
  int n;				// ����� ����� �������
  int nz;				// ����� ��������� ���������
  int error;			// ��� ������ 
  // ��������� ������� � ������� COO
  int* RowCoo;			// ������� �������� ��������� ���������
  int* ColIndex;		// ������ ����� ��������� ���������
  FLOAT_TYPE* Value;	// �������� ��������� ���������
  // ��������� ������� � ������� CSR
  int* RowIndex;		// ������� ������ ����� 
  FLOAT_TYPE* b;		// ������ ������ �����
  FLOAT_TYPE* x;		// ������ �����������
  FLOAT_TYPE err;		// ��������� ������ �������
  
  int cntItr = 1;
  
  if (argc < 1)
  {
	  printf("Args: [1] matrix_file\n");
    return 0;
  }
  
  if (argc > 2)
  {
    cntItr = atoi(argv[2]);
  }
  
  // ������ �������
  error = ReadMTXFile(argv[1], &n, &nz, &ColIndex, &RowCoo, &Value);
  // �������� ������� RowIndex ��� ����������� � CSR
  error = getRowIndex(n, nz, RowCoo, &RowIndex);
  
  if (error != 0)
  {
	  printf("error in read file\n");
	  return 1;
  }
  printf("cntItr: %d\n", cntItr);
  printf("n: %d\nnz: %d\n", n, nz);
  
  b = (FLOAT_TYPE*) malloc(sizeof(FLOAT_TYPE) * n);
  x = (FLOAT_TYPE*) malloc(sizeof(FLOAT_TYPE) * n);

  // ��������� ���������� ����
  for(int i = 0; i < n; i++)
  {
    x[i] = 0.1;
  }
  
  double  res = 0.0;
  
  for(int i = RowIndex[0]; i < RowIndex[1]; i++)
  {
    res += x[ColIndex[i]] * Value[i];
  }
  

  // ���������� ���������� � 1
  toOneBase(n, RowIndex, ColIndex);

  double min_time= 1000.0;
  for(int i = 0; i < cntItr; i++)
  {
    double start = omp_get_wtime();
    MatMV(n, ColIndex, RowIndex, Value, x, b);
    double finish = omp_get_wtime();
    double time = finish - start;
    if(min_time > time) min_time = time;
//    printf("Mat Vector Mult Time: %f s\n", time);
  }
  printf("Mat Vector Mult Time: %f s\n diff: %lf %lf %e\n", min_time, res, b[0], fabs(res-b[0]));
  // ���������� ���������� � 0
  toZeroBase(n, RowIndex, ColIndex);
  
  stat(n, RowIndex, ColIndex);
  
  // ������������ ������
  free(RowCoo);
  free(RowIndex);
  free(ColIndex);
  free(Value);
  free(x);
  free(b);

  return 0;
}
