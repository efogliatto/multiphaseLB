#ifndef SINGLENODET_H
#define SINGLENODET_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

double singleNodeT( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id );

#endif // SINGLENODET_H
