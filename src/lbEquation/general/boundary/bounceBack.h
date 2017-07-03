#ifndef BOUNCEBACK_H 
#define BOUNCEBACK_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void bounceBack( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid );


#endif // BOUNCEBACK_H
