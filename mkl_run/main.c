#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "readFile.h"
#include "MatMV.h"
#include <omp.h>

#define FLOAT_TYPE double

// argv[1] - файл с матрицей
// argv[2] - тип матрицы
int main(int argc, char **argv)
{
  int n;				// число строк матрицы
  int nz;				// число ненулевых элементов
  int error;			// код ошибки 
  // структура матрицы в формате COO
  int* RowCoo;			// индексы столбцов ненулевых элементов
  int* ColIndex;		// индекы строк ненулевых элементов
  FLOAT_TYPE* Value;	// значения ненулевых элементов
  // структура матрицы в формате CSR
  int* RowIndex;		// индексы начала строк 
  FLOAT_TYPE* b;		// вектор правой части
  FLOAT_TYPE* x;		// вектор неизвестных
  FLOAT_TYPE err;		// численная ошибка решения
  
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
  
  // чтение матрицы
  error = ReadMTXFile(argv[1], &n, &nz, &ColIndex, &RowCoo, &Value);
  // создание массива RowIndex для конвертации в CSR
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

  // генерация совместной СЛАУ
  for(int i = 0; i < n; i++)
  {
    x[i] = 0.1;
  }
  
  double  res = 0.0;
  
  for(int i = RowIndex[0]; i < RowIndex[1]; i++)
  {
    res += x[ColIndex[i]] * Value[i];
  }
  

  // приведение индексации с 1
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
  // приведение индексации с 0
  toZeroBase(n, RowIndex, ColIndex);
  
  stat(n, RowIndex, ColIndex);
  
  // освобождение памяти
  free(RowCoo);
  free(RowIndex);
  free(ColIndex);
  free(Value);
  free(x);
  free(b);

  return 0;
}
