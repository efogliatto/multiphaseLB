#ifndef COLLISION_H
#define COLLISION_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

/**
 * @file collision.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Post-collision for every lattice node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 */

void collision( latticeMesh* mesh, macroFields* mfields, lbeField* field );

#endif // COLLISION_H
