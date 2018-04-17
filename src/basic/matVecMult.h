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
 * @param 2D (matrix) array pointer
 * @param 1D (vector) array pointer
 * @param 1D array for result. res = M * v
 * @param Matrix rank
 */

void matVecMult(double** M, double* v, double* res, unsigned int n);

#endif // MATVECMULT_H
