#ifndef WRITEARRAYTOASCIIRAW_H
#define WRITEARRAYTOASCIIRAW_H

#include <latticeMesh.h>

void writeArrayToAsciiRaw( char* fname, scalar** field, latticeMesh* mesh, const uint vsize );

#endif // WRITEARRAYTOASCIIRAW_H
