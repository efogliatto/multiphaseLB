#ifndef FIXEDU_H
#define FIXEDU_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <lbeModel.h>
#include <bdParam.h>
#include <lbParameters.h>

void fixedU( latticeMesh* mesh, macroFields* mfields, double** field, unsigned int bid, lbeModel model, bdParam* bp, lbParameters* lp );


#endif // FIXEDU_H
