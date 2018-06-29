#ifndef READLBEFIELDFROMENSIGHT_H
#define READLBEFIELDFROMENSIGHT_H

#include <latticeMesh.h>

/**
 * @file readLbeFieldFromEnsight.h
 * @author Ezequiel O. Fogliatto
 * @date 27 Jun 2018
 *
 * Read lbe field from ensight file
 *
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readLbeFieldFromEnsight( latticeMesh* mesh, scalar*** field, char* fname );

#endif // READLBEFIELDFROMENSIGHT_H
