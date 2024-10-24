// include header files
#include <math.h>
#include <stdlib.h>
#include "memory_alloc.h"
#include "lattice_reduction.h"



// fills a vector with the squared norms of rows of a matrix
void calculateNormsSqrd(double **matrix, double *dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = dot(matrix[i], matrix[i], n);
    }
}


// performs schnorr-euchner enumeration to solve SVP
// implementation based on pseudocode from:
// International Symposium on Mathematics, Quantum Theory, and Cryptography
double ENUM(double **mu, double *orthogNormsSqrd, int n) {
    // holds current working coefficients
    int *v = allocateIntZeroVector(n);
    v[0] = 1;

    // Vector for zig-zag coefficient pattern
    int *w = allocateIntZeroVector(n);

    // p[k] holds norm of orthogonal projection of v onto lattice, b0,...,bn-k-1
    double *p = allocateDoubleZeroVector(n+1);
    double *c = allocateDoubleZeroVector(n);

    // check for memory allocation errors
    if (v == NULL || w == NULL || p == NULL || c == NULL) {
        deallocateVectors(4, v, w, p, c);
        return -1.0;
    }

    // only consider solutions with norms within radius
    double searchRadius = orthogNormsSqrd[0];
    // k is height in the depth first search tree
    int k = 0;
    int maxHeightreached = 0;
    
    while (1) {
        // calculate p[k] = ||pi[k](s)|| for s given by v
        p[k] = p[k+1] + (pow((v[k] - c[k]), 2) * orthogNormsSqrd[k]);

        if (p[k] < searchRadius && (k > 0 || p[k] > 0)) {
            if (k == 0) {
                // new optimal solution found - update radius
                searchRadius = p[k];
                
            } else {
                // move down in tree
                k--;
                // update vectors
                c[k] = 0;
                for (int i = k + 1; i < n; i++) {
                    c[k] -= mu[i][k] * v[i];
                }
                v[k] = round(c[k]);
                w[k] = 1;
            }
        } else {
            // move up in tree - current vector is not short enough
            k++;
            if (k > n-1) {
                // free allocated memory
                deallocateVectors(4, v, w, p, c);
                // root of search tree reached - return solution
                return pow(searchRadius, 0.5);
            }

            // zig-zag search logic
            if (k > maxHeightreached) {
                maxHeightreached = k;
                v[k]++;
            } else {
                if (v[k] > c[k]) {
                    v[k] -= w[k];
                } else {
                    v[k] += w[k];
                }
                w[k]++;
            }
        }
    }
}
