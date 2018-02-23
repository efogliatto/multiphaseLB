#ifndef HEATSOURCE_H
#define HEATSOURCE_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void heatSource( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // HEATSOURCE_H
