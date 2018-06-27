#ifndef WRITEVECTORFIELD_H
#define WRITEVECTORFIELD_H

#include <latticeMesh.h>

void writeVectorField( char* fname, scalar** field, latticeMesh* mesh, const uint vsize );

#endif // WRITEVECTORFIELD_H
