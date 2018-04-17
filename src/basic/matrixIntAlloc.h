#ifndef MATRIXINTALLOC_H
#define MATRIXINTALLOC_H

/**
 * @file matrixIntAlloc.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Allocation of two-dimensional integer array
 */


/**
 * Allocation of two-dimensional integer array
 * @param nrow Number of rows
 * @param ncol Number of columns
 * @param df Default value for all elements
 * @return Pointer to allocated array
 */

int** matrixIntAlloc(unsigned int nrow, unsigned int ncol, int df);

#endif // MATRIXINTALLOC_H
