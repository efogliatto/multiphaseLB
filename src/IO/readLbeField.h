#ifndef READLBEFIELD_H
#define READLBEFIELD_H

#include <latticeMesh.h>
#include <lbeField.h>

unsigned int readLbeField( struct latticeMesh* mesh, struct lbeField* field, unsigned int vsize, char* fname );

#endif // READLBEFIELD_H
