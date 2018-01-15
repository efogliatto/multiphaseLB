#ifndef SCALARGRADIENT_H
#define SCALARGRADIENT_H

#include <latticeMesh.h>

void scalarGradient( double* grad, double* field, struct latticeMesh* mesh, unsigned int id );

#endif // SCALARGRADIENT_H
