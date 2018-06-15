#ifndef FIXEDEOSP_H
#define FIXEDEOSP_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void fixedEOSp( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid );


#endif // FIXEDEOSP_H
