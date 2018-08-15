#ifndef MACROVELOCITYINLEVEL_H
#define MACROVELOCITYINLEVEL_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file macroVelocityInLevel.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Aug 2018
 *
 * Update macroscopic velocity in level
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param level Node level
 */

void macroVelocityInLevel( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint level );

#endif // MACROVELOCITYINLEVEL_H
