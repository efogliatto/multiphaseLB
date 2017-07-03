#ifndef LISRTVELOCITY_H
#define LISRTVELOCITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

void liSRTVelocity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, double** v, unsigned int id );

#endif // LISRTVELOCITY_H
