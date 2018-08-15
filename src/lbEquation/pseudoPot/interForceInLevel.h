#ifndef INTERFORCEINLEVEL_H
#define INTERFORCEINLEVEL_H

#include <latticeMesh.h>
#include <macroFields.h>


/**
 * @file interForceInLevel.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Aug 2018
 *
 * Interaction force inside node level
 * Updates mfields->Fi
 *
 * @param mesh Lattice mesh
 * @param Fi Macroscopic fields structure
 * @param level Node level
 */

void interForceInLevel( latticeMesh* mesh, macroFields* mfields, uint level );


#endif // INTERFORCEINLEVEL_H
