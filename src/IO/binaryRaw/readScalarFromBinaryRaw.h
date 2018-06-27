#ifndef READSCALARFROMBINARYRAW_H
#define READSCALARFROMBINARYRAW_H

#include <latticeMesh.h>

/**
 * @file readScalarFromBinaryRaw.h
 * @author Ezequiel O. Fogliatto
 * @date 27 Jun 2018
 *
 * Read scalar field from ascii raw file
 *
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readScalarFromBinaryRaw( latticeMesh* mesh, scalar** field, char* fname );

#endif // READSCALARFROMBINARYRAW_H
