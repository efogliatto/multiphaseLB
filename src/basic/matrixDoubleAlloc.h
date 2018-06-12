#ifndef MATRIXDOUBLEALLOC_H
#define MATRIXDOUBLEALLOC_H

#include <dataTypes.h>

/**
 * @file matrixDoubleAlloc.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Allocation of two-dimensional double array
 */


/**
 * Allocation of two-dimensional double array
 * @param nrow Number of rows
 * @param ncol Number of columns
 * @param df Default value for all elements
 * @return Pointer to allocated array
 */

scalar** matrixDoubleAlloc(unsigned int nrow, unsigned int ncol, scalar df);

#endif // MATRIXDOUBLEALLOC_H
