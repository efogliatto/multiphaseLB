#ifndef XUMRTFORCE_H
#define XUMRTFORCE_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void xuMRTForce( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* S, uint id );

#endif // XUMRTFORCE_H
