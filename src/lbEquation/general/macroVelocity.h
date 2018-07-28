#ifndef MACROVELOCITY_H
#define MACROVELOCITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

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

void macroVelocity( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint start, uint end );

#endif // MACROVELOCITY_H
