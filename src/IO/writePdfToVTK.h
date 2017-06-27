#ifndef WRITEPDFTOVTK_H
#define WRITEPDFTOVTK_H

#include <latticeMesh.h>

void writePdfToVTK( char* fname, double** field, struct latticeMesh* mesh );

#endif // WRITEPDFTOVTK_H
