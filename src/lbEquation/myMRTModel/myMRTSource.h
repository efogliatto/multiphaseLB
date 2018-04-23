#ifndef MYMRTSOURCE_H
#define MYMRTSOURCE_H

#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

/**
 * @file myMRTSource.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Heat equation source at node
 *
 * @param mesh Lattice mesh
 * @param mfields Macroscopic fields structure
 * @param field lbField with population distribution
 * @param Gamma Pointer to Source array. Must be already allocated
 * @param id Node index
 */

void myMRTSource( latticeMesh* mesh, macroFields* mfields, lbeField* field, double* Gamma, unsigned int id );

#endif // MYMRTSOURCE_H
