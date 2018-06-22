#ifndef FIXEDRANDOMT_H
#define FIXEDRANDOMT_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <bdParam.h>
#include <lbParameters.h>

void fixedRandomT( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid, lbeModel model, bdParam* bp, lbParameters* lp );


#endif // FIXEDRANDOMT_H
