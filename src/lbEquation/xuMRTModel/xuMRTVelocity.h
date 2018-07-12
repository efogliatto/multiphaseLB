#ifndef XUMRTVELOCITY_H
#define XUMRTVELOCITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void xuMRTVelocity( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar** v, uint id );

#endif // XUMRTVELOCITY_H
