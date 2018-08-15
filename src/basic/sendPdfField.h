#ifndef SENDPDFFIELD_H
#define SENDPDFFIELD_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <mpi.h>
#include <dataTypes.h>

/**
 * @file sendPdfField.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Synchronization of pdf field
 */


/**
 * Synchronization of ghost nodes between patches
 * @brief Synchronization of pdf field
 * @param mesh Pointer to lattice mesh
 * @param fld Pointer to send field
 */

void sendPdfField( latticeMesh* mesh, lbeField* field );

#endif // SENDPDFFIELD_H
