#ifndef INTERFORCE_H
#define INTERFORCE_H

#include <latticeMesh.h>
#include <macroFields.h>


/**
 * @file interForce.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Interaction and total force for all nodes.
 * Updates mfields->Fi
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 */

void interForce( latticeMesh* mesh, macroFields* mfields );


#endif // INTERFORCE_H
