#ifndef COMPWORK_H
#define COMPWORK_H

#include <latticeMesh.h>
#include <macroFields.h>

/**
 * @file macroVelocity.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Update macroscopic velocity for every lattice node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 */

void compWork( latticeMesh* mesh, macroFields* mfields );

#endif // COMPWORK_H
