#ifndef __READ_FILE_H__
#define __READ_FILE_H__

#define FLOAT_TYPE double

#include "stdio.h"

int ReadMTXFile(char* fileName, int* n, int* nz, int** column, int** row, FLOAT_TYPE** val);
int getRowIndex(int n, int nz, int* J, int** row);


#endif