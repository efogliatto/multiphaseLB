#ifndef AVERAGESCALARFIELD_H
#define AVERAGESCALARFIELD_H

#include <latticeMesh.h>
#include <mpi.h>
#include <dataTypes.h>

/**
 * @file averageScalarField.h
 * @author Ezequiel O. Fogliatto
 * @date 22 May 2018
 * @brief Compute average of scalar field across whole domain
 */


/**
 * Compute average of scalar field across whole domain
 * @brief Average of scalar field
 * @param mesh Pointer to lattice mesh
 * @param fld Pointer to field
 */

scalar averageScalarField( latticeMesh* mesh, scalar* fld );

#endif // AVERAGESCALARFIELD_H
