#ifndef FIXEDEOSP_H
#define FIXEDEOSP_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void fixedEOSp( latticeMesh* mesh, macroFields* mfields, double** field, unsigned int bid );


#endif // FIXEDEOSP_H
