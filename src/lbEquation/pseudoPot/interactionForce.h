#ifndef INTERACTIONFORCE_H
#define INTERACTIONFORCE_H

#include <latticeMesh.h>

/**
 * @file interactionForce.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Interaction force for pseuso-potential models
 *
 * @param mesh Lattice mesh
 * @param Ff Array for interaction force
 * @param rho Macroscopic density field
 * @param T Macroscopic temperature field
 * @param id Node index
 */

void interactionForce( latticeMesh* mesh, double Ff[3], double* rho, double* T, unsigned int id );

#endif // INTERACTIONFORCE_H
