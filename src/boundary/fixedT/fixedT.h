#ifndef FIXEDT_H
#define FIXEDT_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void fixedT( latticeMesh* mesh, macroFields* mfields, double** field, unsigned int bid );


#endif // FIXEDT_H
