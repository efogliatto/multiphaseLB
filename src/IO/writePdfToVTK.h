#ifndef WRITEPDFTOVTK_H
#define WRITEPDFTOVTK_H

#include <latticeMesh.h>

void writePdfToVTK( char* fname, scalar** field, latticeMesh* mesh );

#endif // WRITEPDFTOVTK_H
