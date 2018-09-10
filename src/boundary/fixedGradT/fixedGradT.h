#ifndef FIXEDGRADT_H
#define FIXEDGRADT_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <bdParam.h>
#include <lbParameters.h>

void fixedGradT( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid, lbeModel model, bdParam* bp, lbParameters* lp );


#endif // FIXEDGRADT_H
