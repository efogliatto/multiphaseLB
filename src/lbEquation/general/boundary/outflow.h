#ifndef OUTFLOW_H
#define OUTFLOW_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void outflow( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid );

#endif // OUTFLOW_H
