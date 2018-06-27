#ifndef READARRAYFROMASCIIRAW_H
#define READARRAYFROMASCIIRAW_H

#include <latticeMesh.h>

/**
 * @file readArrayFromAsciiRaw.h
 * @author Ezequiel O. Fogliatto
 * @date 27 Jun 2018
 *
 * Read vector field from ascii raw file
 *
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param vsize Array columns
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readArrayFromAsciiRaw( latticeMesh* mesh, scalar*** field, unsigned int vsize, char* fname );

#endif // READARRAYFROMASCIIRAW_H
