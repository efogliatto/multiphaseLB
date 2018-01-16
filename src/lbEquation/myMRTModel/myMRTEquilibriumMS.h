#ifndef MYMRTEQUILIBRIUMMS_H
#define MYMRTEQUILIBRIUMMS_H

#include <latticeMesh.h>
#include <macroFields.h>

void myMRTEquilibriumMS( struct latticeMesh* mesh, struct macroFields* mfields, double* n_eq, double alpha_1, double alpha_2, unsigned int id );

#endif // MYMRTEQUILIBRIUMMS_H
