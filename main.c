// include header files
#include "parse_input.h"
#include "memory_alloc.h"
#include "lattice_reduction.h"
#include "enumeration.h"
#include <stdio.h>



void writeResult(double result) {
    // open file in write mode
    FILE *filePtr = fopen("result.txt", "w");

    // check for error opening file
    if (filePtr == NULL) {
        printf("Error opening file");
        return;
    }
    // write result
    fprintf(filePtr, "%.15lf", result);
    // close file
    fclose(filePtr);
}



int main(int argc, char **argv) {
    // get dimensionality of input
    int dimension = isPerfectSquare(argc - 1);
    if (!dimension) {
        // erronious, 0 value returned -> exit
        printf("Invalid number of arguments");
        return 0;
    }

    // parse input arguments - returns matrix with row basis vectors
    double **basisMatrix = parseInput(argv, dimension);
    // NULL return indicates error - invalid inputs/memory allocation
    if (basisMatrix == NULL) {
        return 0;
    }

    // create copy of basis matrix
    double **basisCopy = copyMatrix(basisMatrix, dimension, dimension);
    if (basisCopy == NULL) {
        // check for memory allocation error
        deallocateMatrices(2, dimension, basisCopy, basisMatrix);
        return 0;
    }
    
    if (!linearlyIndependent(basisCopy, dimension)) {
        // check that matrix is linearly independent
        printf("Basis vectors are not linearly independent\n");
        deallocateMatrices(2, dimension, basisCopy, basisMatrix);
        return 0;
    }
    // finished with copy => free
    deallocateMatrices(1, dimension, basisCopy);


    // rows of orthogonal will hold orthogonal basis vectors
    double **orthogonal = allocateDoubleMatrix(dimension, dimension);
    // mu will hold gram-schmidt coefficients
    double **mu = allocateDoubleMatrix(dimension, dimension);

    // check for memory allocation error
    if (orthogonal == NULL || mu == NULL) {
        // deallocate all matrices
        deallocateMatrices(3, dimension, basisMatrix, orthogonal, mu);
        return 0;
    }

    // reduce lattice basis (in-place)
    LLL(basisMatrix, orthogonal, mu, dimension);
    // update gram-schmidt info for basis
    gramSchmidt(basisMatrix, orthogonal, mu, dimension);
    

    // calculate squared norms of orthogonal basis vectors (in-place)
    double *orthogNormsSqrd = allocateDoubleZeroVector(dimension);
    // check for memory allocation error
    if (orthogNormsSqrd == NULL) {
        deallocateMatrices(3, dimension, basisMatrix, orthogonal, mu);
        return 0;
    }
    calculateNormsSqrd(orthogonal, orthogNormsSqrd, dimension);


    // finished with basisMatrix and orthogonal -> deallocate
    deallocateMatrices(2, dimension, basisMatrix, orthogonal);


    // SE enumeration to solve SVP
    double sol = ENUM(mu, orthogNormsSqrd, dimension);
    // erronious value => allocation error in ENUM execution
    if (sol != -1.0) {
         // write solution
         writeResult(sol);
    }

    // deallocate remaining matrices and vectors
    deallocateMatrices(1, dimension, mu);
    free(orthogNormsSqrd);
}
