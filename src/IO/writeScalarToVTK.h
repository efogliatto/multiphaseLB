#ifndef WRITESCALARTOVTK_H
#define WRITESCALARTOVTK_H

#include <latticeMesh.h>

void writeScalarToVTK( char* fname, double* field, struct latticeMesh* mesh );

#endif // WRITESCALARTOVTK_H
