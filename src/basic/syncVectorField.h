#ifndef SYNCVECTORFIELD_H
#define SYNCVECTORFIELD_H

#include <latticeMesh.h>
#include <mpi.h>

void syncVectorField( struct latticeMesh* mesh, double** fld );

#endif // SYNCVECTORFIELD_H
