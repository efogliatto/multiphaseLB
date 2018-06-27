#ifndef WRITEARRAYTOBINARYRAW_H
#define WRITEARRAYTOBINARYRAW_H

#include <latticeMesh.h>

void writeArrayToBinaryRaw( char* fname, scalar** field, latticeMesh* mesh, const uint vsize );

#endif // WRITEARRAYTOBINARYRAW_H
