#ifndef HEATSOURCE_H
#define HEATSOURCE_H

#include <macroFields.h>
#include <latticeMesh.h>
#include <lbeField.h>

void heatSource( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field );

#endif // HEATSOURCE_H
