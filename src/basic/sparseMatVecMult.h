#ifndef SPARSEMATVECMULT_H
#define SPARSEMATVECMULT_H

#include <stdio.h>

/**
 * @file sparseMatVecMult.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Sparse matrix - vector multiplication
 */


/**
 * Sparse matrix - vector multiplication
 * @param M 2D (matrix) array pointer
 * @param v 1D (vector) array pointer
 * @param res 1D array for result. @p res = @p M * @p v
 * @param nonZero non-zero elements away from diagonal
 * @param n Matrix rank
 * @param nextra Number of non-zero extra elements
 */

void sparseMatVecMult(double** M, double* v, double* res, unsigned int** nonZero, unsigned int n, unsigned int nextra);

#endif // SPARSEMATVECMULT_H
