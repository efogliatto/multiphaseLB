#ifndef MACRODENSITYINLEVEL_H
#define MACRODENSITYINLEVEL_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file macroDensityInLevel.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Update macroscopic density inside level
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param level Node level
 */

void macroDensityInLevel( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint level );

#endif // MACRODENSITYINLEVEL_H
