
//avoid multiple inclusions of header file
#ifndef MEMORY_ALLOC_H
#define MEMORY_ALLOC_H

//include c header files
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

//function declarations
void deallocateMatrices(int numPtrs, int dimension, ...);
void deallocateVectors(int numPtrs, ...);
double **allocateDoubleMatrix(int rows, int cols);
double *allocateDoubleZeroVector(int n);
int *allocateIntZeroVector(int n);
double **copyMatrix(double **original, int rows, int cols);


#endif