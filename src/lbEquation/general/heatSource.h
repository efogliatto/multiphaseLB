#ifndef HEATSOURCE_H
#define HEATSOURCE_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

/**
 * @file heatSource.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Update heat source for every lattice node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 */

void heatSource( latticeMesh* mesh, macroFields* mfields, lbeField* field );

#endif // HEATSOURCE_H
