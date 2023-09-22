#include "readFile.h"
#include <stdlib.h>
#include "mmio.h"


int ReadMTXFile(char* fileName, int* n, int* nz, int** column, int** row, FLOAT_TYPE** val)
{
  FILE* f;
  int ret_code;
  MM_typecode matcode;
  int M, N;
  int i, *I, *J;
  
  if ((f = fopen(fileName, "r")) == NULL) 
  {
    exit(1);
    return -1;
  }

  if (mm_read_banner(f, &matcode) != 0)
  {
    printf("Could not process Matrix Market banner.\n");
    exit(1);
    return -1;
  }

  /*  This is how one can screen matrix types if their application */
  /*  only supports a subset of the Matrix Market data types.      */
  if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
          mm_is_sparse(matcode) )
  {
    printf("Sorry, this application does not support ");
    printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
    exit(1);
    return -1;
  }

  /* find out size of sparse matrix .... */
  if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, nz)) !=0)
  {
    exit(1);
    return -1;
  }
  
  if(M != N)
  {
    printf("M != N \n");
    exit(1);
    return -1;
  }
  
  
  *n = N;

  /* reseve memory for matrices */
  I = (int *) malloc(*nz * sizeof(int));
  J = (int *) malloc(*nz * sizeof(int));
  *val = (double *) malloc(*nz * sizeof(double));

  for (i=0; i<*nz; i++)
  {
      fscanf(f, "%d %d %lf\n", &I[i], &J[i], &(*val)[i]);
      I[i]--;
      J[i]--;
  }

  if (f !=stdin) fclose(f);
  
  *column = I;
  *row = J;
  
  return 0;
}

int getRowIndex(int n, int nz, int* J, int** row)
{
  int i;
  
  *row = (int*)malloc(sizeof(int)*(n + 1));
  if(row == NULL) 
    return -1;

  for (int i = 0; i < (n + 1); i++)
  {
    (*row)[i]=0;
  }

  for (i=0; i<nz; i++)
  {
    (*row)[J[i] + 1]++;
  }
  for (int i = 0; i < n; i++)
  {
    (*row)[i + 1] += (*row)[i];
  }
  
  return 0;
}

int ReadBinaryFile(char* fileName, int* n, int* nz, int** column, int** row, FLOAT_TYPE** val)
{
  FILE* file;
  file = fopen(fileName, "rb");
  if (!file)
    return 1;
  fread(n, sizeof(int), 1, file);
  fread(nz, sizeof(int), 1, file);
  *column = (int*)malloc(sizeof(int)*(*nz));
  *row = (int*)malloc(sizeof(int)*(*n + 1));
  *val = (FLOAT_TYPE*)malloc(sizeof(double)*(*nz));
  fread(*column, sizeof(int), *nz, file);
  fread(*row, sizeof(int), *n + 1, file);
  fread(*val, sizeof(FLOAT_TYPE), *nz, file);
  fclose(file);
  return 0;
}

int ReadIntFile(char* fileName, int* iperm, int n)
{
	int i;
	FILE* f = fopen(fileName, "r");
	if (!f)
	{	
		printf("can't open file\n");
		return 1;
	}
	else 
	{
	for (i = 0; i < n; i++)
	  fscanf(f, "%d\n", &(iperm[i]));
	fclose(f);
	return 0;
	}
}