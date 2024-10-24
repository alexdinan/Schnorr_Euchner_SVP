// include header files
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


// deallocates an arbitrary number of matrix pointers
void deallocateMatrices(int numPtrs, int dimension, ...) {
    va_list args;
    // initialise the argument list
    va_start(args, dimension);

    for (int i = 0; i < numPtrs; i++) {
        // get matrix pointer from arg list
        void **ptr = va_arg(args, void **);
        for (int j = 0; j < dimension; j++) {
            // free each row/vector of matrix
            free(ptr[j]);
        }
        free(ptr);
    }
}


// deallocates an arbitrary number of vector pointers
void deallocateVectors(int numPtrs, ...) {
    va_list args;
    // initialise the argument list
    va_start(args, numPtrs);

    for (int i = 0; i < numPtrs; i++) {
        free(va_arg(args, void *));
    }
}



// dynamically allocates a (rows x cols) 2D-array
double **allocateDoubleMatrix(int rows, int cols) {
    double **matrix = malloc(rows * sizeof(double *));
    if (matrix == NULL) {
        // handle unsucessful allocation
        printf("Memory Allocation Error");
        return NULL;
    }
    for (int i = 0; i < cols; i++) {
        matrix[i] = malloc(cols * sizeof(double));
        if (matrix[i] == NULL) {
            // handle unsucessful allocation
            printf("Memory Allocation Error");
            return NULL;
        }
    }
    return matrix;
}



double *allocateDoubleZeroVector(int n) {
    double *v = malloc(sizeof(double) * n);
    if (v == NULL) {
        // handle unsucessful allocation
        printf("Memory Allocation Error");
    }
    // fill vector with 0s
    for (int i = 0; i < n; i++) {
        v[i] = 0;
    }
    return v;
}


int *allocateIntZeroVector(int n) {
    int *v = malloc(sizeof(int) * n);
    if (v == NULL) {
        // handle unsucessful allocation
        printf("Memory Allocation Error");
    }
    // fill vector with 0s
    for (int i = 0; i < n; i++) {
        v[i] = 0;
    }
    return v;
}



// copy a matrix in-place
double **copyMatrix(double **original, int rows, int cols) {
    double **copy = allocateDoubleMatrix(rows, cols);

    // check for allocation error
    if (copy == NULL) {
        return NULL;
    }
    // copy matrix contents
    for (int i = 0; i < rows; i++) {
        for (int j =0; j < cols; j++) {
            copy[i][j] = original[i][j];
        }
    }
    return copy;
}
