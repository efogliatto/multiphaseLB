#ifndef READSCALARFROMPVTU_H
#define READSCALARFROMPVTU_H

#include <latticeMesh.h>

/**
 * @file readScalarFromPvtu.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Dic 2018
 * @brief Read scalar field from pvtu file
 */

/**
 * @brief Read vector field from pvtu file and updates @p field
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readScalarFromPvtu( latticeMesh* mesh, scalar** field, char* fname );

#endif // READSCALARFROMPVTU_H
