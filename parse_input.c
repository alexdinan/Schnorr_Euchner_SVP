// include header files
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "memory_alloc.h"


// returns sqrt(n) if n is a perfect square >= 1 otherwise 0
int isPerfectSquare(int n) {
    int guess = 1;
    while ((guess * guess) < n) {
        guess++;
    }
    if (guess * guess == n) {
        return guess;
    } else {
        return 0;
    }
}


// returns 1 if a string is a valid real number, 0 otherwise
int isRealNumber(char *string, int start, int end) {
    int seenDecimalPoint = 0;
    // if empty string return 0
    if (start == end) {
        return 0;
    }

    // check validity of every character
    for (int i = start; i < end; i++) {
        if (!isdigit(string[i])) {
            // real numbers can contain one decimal point
            if (string[i] == '.' && !seenDecimalPoint) {
                seenDecimalPoint = 1;
            } else if (i == start && string[i] == '-') {
                 // real numbers can start with a negative sign
            } else {
                // otherwise not a number
                return 0;
            }
        }
    }
    return 1;
}



double parseArg(char *arg, int leadingBracket,
                int trailingBracket, int *errorFlag) {
    // ensure arg starts with '[' / ']'
    if (leadingBracket && arg[0] != '[') {
        *errorFlag = 1;
        return 0;
    }
    if (trailingBracket && arg[strlen(arg) - 1] != ']') {
        *errorFlag = 1;
        return 0;
    }

    // check that argument is a valid real number
    if (isRealNumber(arg, leadingBracket, strlen(arg) - trailingBracket)) {
        // convert to float
        return atof(arg+leadingBracket);
    } else {
        // set error flag
        *errorFlag = 1;
        return 0;
    }
}



double **parseInput(char **args, int dimensions) {
    // dynamically allocate matrix
    double **matrix = allocateDoubleMatrix(dimensions, dimensions);
    // check for memory allocation error
    if (matrix == NULL) {
        return NULL;
    }

    int errorBit = 0;
    int *errorFlag = &errorBit;
    int counter = 1;
    // parse arguments and fill matrix
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            // parse argument
            double convertedArg = parseArg(args[counter], j == 0,
                                            j == dimensions - 1, errorFlag);

            // check if an error occured
            if (*errorFlag == 1) {
                printf("Contains invalid input arguments");
                return NULL;
            }

            // add argument to matrix
            matrix[i][j] = convertedArg;
            counter++;
        }
    }
    return matrix;
}
