#ifndef READSCALARFROMASCIIRAW_H
#define READSCALARFROMASCIIRAW_H

#include <latticeMesh.h>

/**
 * @file readScalarFromAsciiRaw.h
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

uint readScalarFromAsciiRaw( latticeMesh* mesh, scalar** field, char* fname );

#endif // READSCALARFROMASCIIRAW_H
