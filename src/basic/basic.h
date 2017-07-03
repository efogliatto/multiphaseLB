#ifndef BASIC_H
#define BASIC_H

#include <stdlib.h>

double** matrixDoubleAlloc(unsigned int nrow, unsigned int ncol, double df);

int** matrixIntAlloc(unsigned int nrow, unsigned int ncol, int df);

#include <matVecMult.h>

#endif // BASIC_H
