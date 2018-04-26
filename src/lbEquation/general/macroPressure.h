#ifndef MACROPRESSURE_H
#define MACROPRESSURE_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file macroPressure.h
 * @author Ezequiel O. Fogliatto
 * @date 26 Apr 2018
 *
 * Update macroscopic pressure
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 */

void macroPressure( latticeMesh* mesh, macroFields* mfields, lbeField* field );

#endif // MACROPRESSURE_H
