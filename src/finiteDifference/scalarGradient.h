#ifndef SCALARGRADIENT_H
#define SCALARGRADIENT_H

#include <latticeMesh.h>

/**
 * @file scalarGradient.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Gradient of scalar field at node
 *
 * @param grad Pointer for gradient result
 * @param field Macroscopic scalar field
 * @param mesh Lattice mesh
 * @param id Node index
 */

void scalarGradient( scalar* grad, scalar* field, latticeMesh* mesh, uint id );

#endif // SCALARGRADIENT_H
