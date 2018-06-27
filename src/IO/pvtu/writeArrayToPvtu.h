#ifndef WRITEARRAYTOPVTU_H
#define WRITEARRAYTOPVTU_H

#include <latticeMesh.h>

void writeArrayToPvtu( char* fname, scalar** field, latticeMesh* mesh, const uint vsize );

#endif // WRITEARRAYTOPVTU_H
