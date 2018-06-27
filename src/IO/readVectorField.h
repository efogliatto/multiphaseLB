#ifndef READVECTORFIELD_H
#define READVECTORFIELD_H

#include <latticeMesh.h>

/**
 * @file readVectorField.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Dic 2018
 * @brief Read vector field from pvtu file
 */

/**
 * @brief Read vector field and update @p field
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param vsize Number of components per vector
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readVectorField( latticeMesh* mesh, scalar*** field, uint vsize, char* fname );

#endif // READVECTORFIELD_H
