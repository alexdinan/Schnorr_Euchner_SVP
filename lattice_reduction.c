// include header files
#include <math.h>
#include "memory_alloc.h"



// checks linear independence of a square matrix
int linearlyIndependent(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        // find position of first non-zero element in row i
        int j;
        for (j = 0; j < n; j++) {
            if (matrix[i][j] != 0) {
                break;
            }
        }

        // have found row of 0s => linearly dependent
        if (j == n) {
            return 0;
        }

        // perform row reduction
        for (int k = i + 1; k < n; k++) {
            double factor = matrix[k][j] / matrix[i][j];
            for (int l = j; l < n; l++) {
                matrix[k][l] -= factor * matrix[i][l];
            }
        }
    }
    // no 0 rows found => independent
    return 1;
}



// returns the dot product of two n-dimensional vectors
double dot(double *v1, double *v2, int n) {
    double result = 0;
    // result = v1[0]*v2[0] + ... + v1[n-1]*v2[n-1]
    for (int i = 0; i < n; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}


// swaps two rows of a matrix in-place
void swapRows(double **matrix, int r1, int r2, int cols) {
    for (int i = 0; i < cols; i++) {
        double temp = matrix[r1][i];
        matrix[r1][i] = matrix[r2][i];
        matrix[r2][i] = temp;
    }
}


// orthogonalise a matrix of row basis vectors in-place
void gramSchmidt(double **matrix, double **orthogonal, double **mu, int n) {
    // copy first basis vector into orthogonal basis
    for (int i = 0; i < n; i++) {
        orthogonal[0][i] = matrix[0][i];
    }

    // process remaining vectors
    for (int i = 1; i < n; i++) {
        // initially - copy vector
        for (int j = 0; j < n; j++) {
            orthogonal[i][j] = matrix[i][j];
        }

        for (int k = 0; k < i; k++) {
            // calculate gram-schmidt coefficient - store in mu
            mu[i][k] = dot(matrix[i], orthogonal[k], n) /
                        dot(orthogonal[k], orthogonal[k], n);

            // calculate orthogonal row basis vectors
            for (int l = 0; l < n; l++) {
                orthogonal[i][l] -= mu[i][k] * orthogonal[k][l];
            }
        }
    }
}


// performs in-place lll lattice reduction on matrix of row basis vectors
// implemented based on pseudocode from:
// https://en.wikipedia.org/wiki/Lenstra%E2%80%93Lenstra%E2%80%93Lov%C3%A1sz_lattice_basis_reduction_algorithm
void LLL(double **matrix, double **orthogonal, double **mu, int n) {
    // compute orthogonal basis matrix
    gramSchmidt(matrix, orthogonal, mu, n);

    // start at first row vector until all have been sufficiently reduced
    int pos = 1;
    while (pos < n) {
        for (int i = pos-1; i > -1; i--) {
            // check size condition
            if (mu[pos][i] > 0.5 || mu[pos][i] < -0.5) {
                // failed - reduce size of working vector
                for (int j = 0; j < n; j++) {
                    matrix[pos][j] -= round(mu[pos][i]) * matrix[i][j];
                }
                // re-compute orthogonal basis / GS coefficients
                gramSchmidt(matrix, orthogonal, mu, n);
            }
        }

        // check lovasz condition
        if (dot(orthogonal[pos], orthogonal[pos], n) >=
            (0.75 - pow(mu[pos][pos-1], 2)) *
            dot(orthogonal[pos-1], orthogonal[pos-1], n)) {
            // passed - work on the next vector
            pos++;
        } else {
            // failed - swap vectors, recompute GS and work on previous vector
            swapRows(matrix, pos, pos-1, n);
            gramSchmidt(matrix, orthogonal, mu, n);
            pos = (pos > 1) ? pos-1 : 1;
        }
    }
}
