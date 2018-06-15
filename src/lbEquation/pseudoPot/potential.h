#ifndef POTENTIAL_H
#define POTENTIAL_H

#include <latticeMesh.h>

/**
 * @file potential.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Potential based of Yuan scheme
 *
 * @param mesh Lattice mesh
 * @param rho Macroscopic density at node
 * @param T Macroscopic temperature at node
 * @return Potential @p id
 */

scalar potential( latticeMesh* mesh, scalar rho, scalar T );

#endif // POTENTIAL_H
