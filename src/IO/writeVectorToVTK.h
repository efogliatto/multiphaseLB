#ifndef WRITEVECTORTOVTK_H
#define WRITEVECTORTOVTK_H

#include <latticeMesh.h>

void writeVectorToVTK( char* fname, double** field, struct latticeMesh* mesh );

#endif // WRITEVECTORTOVTK_H
