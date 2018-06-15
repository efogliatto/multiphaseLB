#ifndef WRITEVECTORTOVTK_H
#define WRITEVECTORTOVTK_H

#include <latticeMesh.h>

void writeVectorToVTK( char* fname, scalar** field, latticeMesh* mesh );

#endif // WRITEVECTORTOVTK_H
