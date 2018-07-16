#ifndef XUMRTEQUILIBRIUMMS_H
#define XUMRTEQUILIBRIUMMS_H

#include <latticeMesh.h>
#include <macroFields.h>

/**
 * @file xuMRTEquilibriumMS.h
 * @author Ezequiel O. Fogliatto
 * @date 16 Jul 2018
 *
 * Equilibrium distribution in momentum space
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param n_eq Pointer to distribution in momentum space. Must be already allocated
 * @param id Node index
 */

void xuMRTEquilibriumMS( latticeMesh* mesh, macroFields* mfields, scalar* m_eq, uint id );

#endif // XUMRTEQUILIBRIUMMS_H
