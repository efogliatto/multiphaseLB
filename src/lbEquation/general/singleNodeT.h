#ifndef SINGLENODET_H
#define SINGLENODET_H

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

/**
 * @file singleNodeT.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Macroscopic temperature at single lattice node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param id Node index
 * @return Temperature at single node @p id
 */

scalar singleNodeT( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint id );

#endif // SINGLENODET_H
