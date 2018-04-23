#ifndef EQUILIBRIUM_H
#define EQUILIBRIUM_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file equilibrium.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Equilibrium distribution for every lattice node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 */

void equilibrium( latticeMesh* mesh, macroFields* mfields, lbeField* field );


#endif // EQUILIBRIUM_H
