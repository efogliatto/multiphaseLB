#ifndef UPDATEBOUNDARIES_H
#define UPDATEBOUNDARIES_H

#include <lbeField.h>
#include <macroFields.h>
#include <latticeMesh.h>

void updateBoundaries( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // UPDATEBOUNDARIES_H
