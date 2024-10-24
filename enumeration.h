
//avoid multiple inclusions of header file
#ifndef ENUMERATION_H
#define ENUMERATION_H

//include c header files
#include <math.h>
#include <stdlib.h>
#include "memory_alloc.h"

//function declarations
void calculateNormsSqrd(double **matrix, double *dest, int n);
double ENUM(double **mu, double *orthogNormsSqrd, int n);

#endif