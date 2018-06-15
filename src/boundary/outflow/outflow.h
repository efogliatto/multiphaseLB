#ifndef OUTFLOW_H
#define OUTFLOW_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void outflow( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid );

#endif // OUTFLOW_H
