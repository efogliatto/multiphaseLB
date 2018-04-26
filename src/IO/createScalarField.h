#ifndef CREATESCALARFIELD_H
#define CREATESCALARFIELD_H

#include <latticeMesh.h>
#include <dataTypes.h>

/**
 * @file createScalarField.h
 * @author Ezequiel O. Fogliatto
 * @date 26 Apr 2018
 * 
 * Creation of Scalar type field
 *
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field array
 * @param fname Field name
 * @param options Creation options: MUST_READ, NO_READ
 */


void createScalarField( latticeMesh* mesh, scalar** field, char* fname, fieldOpt options );

#endif // CREATESCALARFIELD_H
