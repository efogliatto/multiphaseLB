#ifndef FIXEDEOSP_H
#define FIXEDEOSP_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void fixedEOSp( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid );


#endif // FIXEDEOSP_H
