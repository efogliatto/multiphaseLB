#ifndef INVSCALARGRADIENT_H
#define INVSCALARGRADIENT_H

#include <latticeMesh.h>

/**
 * @file invScalarGradient.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Gradient of inverse of scalar field at node
 *
 * @param grad Pointer for gradient result
 * @param field Macroscopic scalar field
 * @param mesh Lattice mesh
 * @param id Node index
 */

void invScalarGradient( double* grad, double* field, latticeMesh* mesh, unsigned int id );

#endif // INVSCALARGRADIENT_H
