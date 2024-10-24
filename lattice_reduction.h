
//avoid multiple inclusions of header file
#ifndef LATTICE_REDUCTION_H
#define LATTICE_REDUCTION_H

//include c header files
#include <math.h>
#include "memory_alloc.h"

//function declarations
double dot(double *v1, double *v2, int n);
void swapRows(double **matrix, int r1, int r2, int cols);
void gramSchmidt(double **matrix, double **orthogonal, double **mu, int n);
void LLL(double **matrix, double **orthogonal, double **mu, int n);
int linearlyIndependent(double **matrix, int n);

#endif