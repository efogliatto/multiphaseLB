#ifndef SYNCSCALARFIELD_H
#define SYNCSCALARFIELD_H

#include <latticeMesh.h>
#include <mpi.h>

void syncScalarField( struct latticeMesh* mesh, double* fld );

#endif // SYNCSCALARFIELD_H
