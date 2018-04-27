#ifndef LIMRSURFACETENSION_H
#define LIMRTSURFACETENSION_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void liMRTSurfaceTension( latticeMesh* mesh, macroFields* mfields, lbeField* field, double* C, unsigned int id );

#endif // LIMRTSURFACETENSION_H
