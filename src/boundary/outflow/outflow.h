#ifndef OUTFLOW_H
#define OUTFLOW_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void outflow(  latticeMesh* mesh,  macroFields* mfields,  double** field, unsigned int bid );

#endif // OUTFLOW_H
