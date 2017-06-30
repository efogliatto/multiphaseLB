#ifndef READVECTORFIELD_H
#define READVECTORFIELD_H

#include <latticeMesh.h>

unsigned int readVectorField( struct latticeMesh* mesh, double*** field, unsigned int vsize, char* fname );

#endif // READVECTORFIELD_H
