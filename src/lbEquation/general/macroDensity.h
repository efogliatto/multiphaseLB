#ifndef MACRODENSITY_H
#define MACRODENSITY_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file macroDensity.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Update macroscopic density
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param start Node start local index
 * @param start Node end local index
 */

void macroDensity( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint start, uint end );

#endif // MACRODENSITY_H
