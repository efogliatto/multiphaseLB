#ifndef LIMRTFORCE_H
#define LIMRTFORCE_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void liMRTForce( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* S, uint id );

#endif // LIMRTFORCE_H
