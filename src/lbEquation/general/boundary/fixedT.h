#ifndef FIXEDT_H
#define FIXEDT_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void fixedT( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid );


#endif // FIXEDT_H
