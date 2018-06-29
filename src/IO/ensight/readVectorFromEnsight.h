#ifndef READVECTORFROMENSIGHT_H
#define READVECTORFROMENSIGHT_H

#include <latticeMesh.h>

/**
 * @file readVectorFromEnsight.h
 * @author Ezequiel O. Fogliatto
 * @date 29 Jun 2018
 *
 * Read vector field from ensight file
 *
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param fname Field name
 * @return Status. Correct if different from zero
 */

uint readVectorFromEnsight( latticeMesh* mesh, scalar*** field, char* fname );

#endif // READVECTORFROMENSIGHT_H
