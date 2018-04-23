#ifndef VECTORDIVERGENCE_H
#define VECTORDIVERGENCE_H

#include <latticeMesh.h>

/**
 * @file vectorDivergence.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Divergence of vector field at node
 *
 * @param field Macroscopic vector field
 * @param mesh Lattice mesh
 * @param id Node index
 * @return Vector divergence at node
 */

double vectorDivergence( double** field, latticeMesh* mesh, unsigned int id );

#endif // VECTORDIVERGENCE_H
