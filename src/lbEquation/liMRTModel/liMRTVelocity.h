#ifndef LIMRTVELOCITY_H
#define LIMRTVELOCITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void liMRTVelocity( latticeMesh* mesh, macroFields* mfields, lbeField* field, double** v, unsigned int id );

#endif // LIMRTVELOCITY_H
