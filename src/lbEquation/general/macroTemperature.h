#ifndef MACROTEMPERATURE_H
#define MACROTEMPERATURE_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file macroTemperature.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Update macroscopic temperature for every lattice node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 */

void macroTemperature( latticeMesh* mesh, macroFields* mfields, lbeField* field );

#endif // MACROTEMPERATURE_H
