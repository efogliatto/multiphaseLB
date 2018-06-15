#ifndef CREATEVECTORFIELD_H
#define CREATEVECTORFIELD_H

#include <latticeMesh.h>
#include <dataTypes.h>

/**
 * @file createVectorField.h
 * @author Ezequiel O. Fogliatto
 * @date 26 Apr 2018
 * 
 * Creation of Vector type field
 *
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param vsize Number of elements per vector
 * @param fname Field name
 * @param options Creation options: MUST_READ, NO_READ
 */

void createVectorField( latticeMesh* mesh, scalar*** field, uint vsize, char* fname, fieldOpt options );

#endif // CREATEVECTORFIELD_H
