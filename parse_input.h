
//avoid multiple inclusions of header file
#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

// Include necessary header files
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "memory_alloc.h"

// Function declarations
int isPerfectSquare(int n);
int isRealNumber(char *string, int start, int end);
double parseArg(char *arg, int leadingBracket, int trailingBracket, int *errorFlag);
double **parseInput(char **args, int dimensions);

#endif