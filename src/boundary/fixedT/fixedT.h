#ifndef FIXEDT_H
#define FIXEDT_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <bdParam.h>
#include <lbParameters.h>

void fixedT( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid, lbeModel model, bdParam* bp, lbParameters* lp );


#endif // FIXEDT_H
