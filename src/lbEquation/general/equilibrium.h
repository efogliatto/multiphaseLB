#ifndef EQUILIBRIUM_H
#define EQUILIBRIUM_H

#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>


void equilibrium( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );


#endif // EQUILIBRIUM_H
