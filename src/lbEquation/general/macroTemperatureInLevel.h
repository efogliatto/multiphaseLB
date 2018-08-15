#ifndef MACROTEMPERATUREINLEVEL_H
#define MACROTEMPERATUREINLEVEL_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file macroTemperatureInLevel.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Aug 2018
 *
 * Update macroscopic temperature inside node level
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param level Node level
 */

void macroTemperatureInLevel( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint level );

#endif // MACROTEMPERATUREINLEVEL_H
