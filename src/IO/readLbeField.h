#ifndef READLBEFIELD_H
#define READLBEFIELD_H

#include <latticeMesh.h>
#include <lbeField.h>

/**
 * @file readLbeField.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Apr 2018
 * @brief Read lbe field from vtu file
 * @param mesh Lattice mesh
 * @param field Field to be loaded
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readLbeField( latticeMesh* mesh, lbeField* field, char* fname );

#endif // READLBEFIELD_H
