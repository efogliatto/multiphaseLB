#ifndef UPDATEBOUNDARIES_H
#define UPDATEBOUNDARIES_H

#include <lbeField.h>
#include <macroFields.h>
#include <latticeMesh.h>

/**
 * @file updateBoundaries.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Apply boundary conditions
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 */

void updateBoundaries( latticeMesh* mesh, macroFields* mfields, lbeField* field );

#endif // UPDATEBOUNDARIES_H
