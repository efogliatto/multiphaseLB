#ifndef SYNCPDFFIELD_H
#define SYNCPDFFIELD_H

#include <latticeMesh.h>
#include <mpi.h>

/**
 * @file syncPdfField.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Synchronization of pdf field
 */


/**
 * Synchronization of ghost nodes betwenn patches
 * @brief Synchronization of pdf field
 * @param mesh Pointer to lattice mesh
 * @param fld Pointer to sync field
 */

void syncPdfField( latticeMesh* mesh, double** fld );

#endif // SYNCPDFFIELD_H
