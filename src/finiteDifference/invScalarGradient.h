#ifndef INVSCALARGRADIENT_H
#define INVSCALARGRADIENT_H

#include <latticeMesh.h>

void invScalarGradient( double* grad, double* field, struct latticeMesh* mesh, unsigned int id );

#endif // INVSCALARGRADIENT_H
