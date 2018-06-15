#ifndef UNIFORMHEATFLUX_H
#define UNIFORMHEATFLUX_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void uniformHeatFlux(  latticeMesh* mesh,  macroFields* mfields,  scalar** field, uint bid );


#endif // UNIFORMHEATFLUX_H
