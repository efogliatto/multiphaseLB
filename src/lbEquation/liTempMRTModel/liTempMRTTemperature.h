#ifndef LITEMPMRTTEMPERATURE_H
#define LITEMPMRTTEMPERATURE_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file liTempMRTTemperature.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Macroscopic temperature at node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param id Node index
 * @return Temperature at node @p id
 */

scalar liTempMRTTemperature( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint id );

#endif // LITEMPMRTTEMPERATURE_H
