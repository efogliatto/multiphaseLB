#ifndef LIMRTSURFACETENSION_H
#define LIMRTSURFACETENSION_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void liMRTSurfaceTension( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* C, uint id );

#endif // LIMRTSURFACETENSION_H
