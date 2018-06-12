#ifndef SYNCVECTORFIELD_H
#define SYNCVECTORFIELD_H

#include <latticeMesh.h>
#include <mpi.h>
#include <dataTypes.h>

/**
 * @file syncVectorField.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Synchronization of vector (3 elements) field
 */


/**
 * Synchronization of ghost nodes betwenn patches for vector field
 * @brief Synchronization of vector (3 elements) field
 * @param mesh Pointer to lattice mesh
 * @param fld Pointer to sync field
 */

void syncVectorField( latticeMesh* mesh, scalar** fld );

#endif // SYNCVECTORFIELD_H
