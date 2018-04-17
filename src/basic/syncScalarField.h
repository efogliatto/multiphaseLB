#ifndef SYNCSCALARFIELD_H
#define SYNCSCALARFIELD_H

#include <latticeMesh.h>
#include <mpi.h>

/**
 * @file syncScalarField.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Synchronization of scalar field
 */


/**
 * Synchronization of ghost nodes between patches
 * @brief Synchronization of scalar field
 * @param mesh Pointer to lattice mesh
 * @param fld Pointer to sync field
 */

void syncScalarField( latticeMesh* mesh, double* fld );

#endif // SYNCSCALARFIELD_H
