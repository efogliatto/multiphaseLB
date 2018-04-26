#ifndef CREATELBEFIELD_H
#define CREATELBEFIELD_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <dataTypes.h>

/**
 * @file createLbeField.h
 * @author Ezequiel O. Fogliatto
 * @date 26 Apr 2018
 * 
 * Creation of LBE type field
 *
 * @param mesh Pointer to lattice mesh
 * @param field Pointer to field
 * @param fname Field name
 * @param options Creation options: MUST_READ, NO_READ
 */

void createLbeField( latticeMesh* mesh, lbeField* field, char* fname, fieldOpt options );

#endif // CREATELBEFIELD_H
