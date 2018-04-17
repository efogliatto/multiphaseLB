#ifndef MATVECMULT_H
#define MATVECMULT_H

#include <stdio.h>

/**
 * @file matVecMult.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Matrix - vector multiplication
 */


/**
 * Matrix - vector multiplication
 * @param M 2D (matrix) array pointer
 * @param v 1D (vector) array pointer
 * @param res 1D array for result. @p res = @p M * @p v
 * @param n Matrix rank
 */

void matVecMult(double** M, double* v, double* res, unsigned int n);

#endif // MATVECMULT_H
