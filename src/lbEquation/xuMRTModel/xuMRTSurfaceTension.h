#ifndef XUMRTSURFACETENSION_H
#define XUMRTSURFACETENSION_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void xuMRTSurfaceTension( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* C, uint id );

#endif // XUMRTSURFACETENSION_H
