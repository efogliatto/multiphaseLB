#ifndef READARRAYFROMBINARYRAW_H
#define READARRAYFROMBINARYRAW_H

#include <latticeMesh.h>

/**
 * @file readArrayFromBinaryRaw.h
 * @author Ezequiel O. Fogliatto
 * @date 27 Jun 2018
 *
 * Read vector field from binary raw file
 *
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param vsize Array columns
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readArrayFromBinaryRaw( latticeMesh* mesh, scalar*** field, unsigned int vsize, char* fname );

#endif // READARRAYFROMBINARYRAW_H
