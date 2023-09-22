#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mkl_pardiso.h"
#include "mkl_types.h"
#include "mkl_spblas.h"
#include <string.h>

#include "MatMV.h"

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
void MatMV(int n, int* col, int* row, FLOAT_TYPE* val, FLOAT_TYPE* x, FLOAT_TYPE* res){
  // Descriptor of main sparse matrix properties
  struct matrix_descr descrA;
  // Structure with sparse matrix stored in CSR format
  sparse_matrix_t       csrA;
  sparse_operation_t    transA;

  sparse_status_t stat;
  
  transA = SPARSE_OPERATION_NON_TRANSPOSE;
  descrA.type = SPARSE_MATRIX_TYPE_GENERAL;

  mkl_sparse_d_create_csr(&csrA, SPARSE_INDEX_BASE_ONE, n, n, row, row + 1, col, val);

  // Compute residual
  stat = mkl_sparse_d_mv(transA, 1.0, csrA, descrA, x, 0.0, res);

  if(stat != SPARSE_STATUS_SUCCESS )
    printf("MULT_ERROR %d ", stat);
  
}