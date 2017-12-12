#ifndef MYMRTSOURCE_H
#define MYMRTSOURCE_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void myMRTSource( struct latticeMesh* mesh, struct macroFields* mfields, double* Gamma, unsigned int id );

#endif // MYMRTSOURCE_H
