#ifndef UNIFORMHEATFLUX_H
#define UNIFORMHEATFLUX_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void uniformHeatFlux( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid );


#endif // UNIFORMHEATFLUX_H
