#ifndef MYMRTTEMPERATURE_H
#define MYMRTTEMPERATURE_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file myMRTTemperature.h
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

scalar myMRTTemperature( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint id );

#endif // MYMRTTEMPERATURE_H
