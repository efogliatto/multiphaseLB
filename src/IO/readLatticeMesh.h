#ifndef READLATTICEMESH_H
#define READLATTICEMESH_H

#include <latticeMesh.h>

/**
 * @file readLatticeMesh.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Read lattice mesh elements and info from file
 * Read lattice mesh elements and info from distributed files
 * @param pid Process tag
 * @return Lattice Mesh structure
 */

latticeMesh readLatticeMesh( unsigned int pid );

#endif // READLATTICEMESH_H
