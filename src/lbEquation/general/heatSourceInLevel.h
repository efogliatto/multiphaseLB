#ifndef HEATSOURCEINLEVEL_H
#define HEATSOURCEINLEVEL_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

/**
 * @file heatSourceInLevel.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Aug 2018
 *
 * Update heat source inside node level
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param level Node level
 */

void heatSourceInLevel( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint level );

#endif // HEATSOURCEINLEVEL_H
