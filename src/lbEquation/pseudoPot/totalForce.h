#ifndef TOTALFORCE_H
#define TOTALFORCE_H

#include <latticeMesh.h>

void totalForce( struct latticeMesh* mesh, double F[3], double* rho, double* T, unsigned int id );

#endif // TOTALFORCE_H
