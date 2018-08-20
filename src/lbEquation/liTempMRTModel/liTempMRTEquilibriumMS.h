#ifndef LITEMPMRTEQUILIBRIUMMS_H
#define LITEMPMRTEQUILIBRIUMMS_H

#include <latticeMesh.h>
#include <macroFields.h>

/**
 * @file liTempMRTEquilibriumMS.h
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

void liTempMRTEquilibriumMS( latticeMesh* mesh, macroFields* mfields, scalar* n_eq, uint id );

#endif // LITEMPMRTEQUILIBRIUMMS_H
