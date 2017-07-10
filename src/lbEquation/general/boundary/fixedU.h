#ifndef FIXEDU_H
#define FIXEDU_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void fixedU( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid );


#endif // FIXEDU_H
