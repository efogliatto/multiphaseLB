#ifndef LITEMPMRTSOURCE_H
#define LITEMPMRTSOURCE_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

/**
 * @file liTempMRTSource.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Heat equation source at node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param Gamma Pointer to Source array. Must be already allocated
 * @param id Node index
 */

void liTempMRTSource( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* Gamma, uint id );

#endif // LITEMPMRTSOURCE_H
