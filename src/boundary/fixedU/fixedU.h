#ifndef FIXEDU_H
#define FIXEDU_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void fixedU(  latticeMesh* mesh,  macroFields* mfields,  double** field, unsigned int bid );


#endif // FIXEDU_H
