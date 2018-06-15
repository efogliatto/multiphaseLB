#ifndef MYMRTEQUILIBRIUMMS_H
#define MYMRTEQUILIBRIUMMS_H

#include <latticeMesh.h>
#include <macroFields.h>

/**
 * @file myMRTEquilibriumMS.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Equilibrium distribution in momentum space
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param n_eq Pointer to distribution in momentum space. Must be already allocated
 * @param alpha_1 Model constant
 * @param alpha_2 Model constant
 * @param id Node index
 */

void myMRTEquilibriumMS( latticeMesh* mesh, macroFields* mfields, scalar* n_eq, scalar alpha_1, scalar alpha_2, uint id );

#endif // MYMRTEQUILIBRIUMMS_H
