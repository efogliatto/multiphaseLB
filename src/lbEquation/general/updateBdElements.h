#ifndef UPDATEBDELEMENTS_H
#define UPDATEBDELEMENTS_H

#include <lbeField.h>
#include <macroFields.h>
#include <latticeMesh.h>

void updateBdElements( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // UPDATEBDELEMENTS_H
