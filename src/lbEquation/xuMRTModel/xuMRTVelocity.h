#ifndef LIMRTVELOCITY_H
#define LIMRTVELOCITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void liMRTVelocity( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar** v, uint id );

#endif // LIMRTVELOCITY_H
