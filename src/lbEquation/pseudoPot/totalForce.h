#ifndef TOTALFORCE_H
#define TOTALFORCE_H

#include <latticeMesh.h>

/**
 * @file interactionForce.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Total force for pseuso-potential models
 * Computes interaction force and adds body force
 *
 * @param mesh Lattice mesh
 * @param F Array for interaction force
 * @param rho Macroscopic density field
 * @param T Macroscopic temperature field
 * @param id Node index
 */

void totalForce( latticeMesh* mesh, scalar F[3], scalar* rho, scalar* T, uint id );

#endif // TOTALFORCE_H
