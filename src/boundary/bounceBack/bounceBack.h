#ifndef BOUNCEBACK_H 
#define BOUNCEBACK_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void bounceBack( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid );


#endif // BOUNCEBACK_H
