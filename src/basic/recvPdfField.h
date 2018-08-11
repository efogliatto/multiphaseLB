#ifndef RECVPDFFIELD_H
#define RECVPDFFIELD_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <mpi.h>
#include <dataTypes.h>

/**
 * @file recvPdfField.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Synchronization of pdf field
 */


/**
 * Synchronization of ghost nodes betwenn patches
 * @brief Synchronization of pdf field
 * @param mesh Pointer to lattice mesh
 * @param fld Pointer to recv field
 */

void recvPdfField( latticeMesh* mesh, lbeField* field );

#endif // RECVPDFFIELD_H
