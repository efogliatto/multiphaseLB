#ifndef LIMRTVELOCITY_H
#define LIMRTVELOCITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void liMRTVelocity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, double v[3], unsigned int id );

#endif // LIMRTVELOCITY_H
