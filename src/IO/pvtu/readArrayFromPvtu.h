#ifndef READARRAYFROMPVTU_H
#define READARRAYFROMPVTU_H

#include <latticeMesh.h>

/**
 * @file readArrayFromPvtu.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Dic 2018
 * @brief Read vector field from pvtu file
 */

/**
 * @brief Read vector field from pvtu file and updates @p field
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param vsize Number of components per vector
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readArrayFromPvtu( latticeMesh* mesh, scalar*** field, uint vsize, char* fname );

#endif // READARRAYFROMPVTU_H
