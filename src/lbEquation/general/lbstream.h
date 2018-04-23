#ifndef LBSTREAM_H
#define LBSTREAM_H

#include <latticeMesh.h>
#include <lbeField.h>

/**
 * @file lbstream.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Field streaming
 *
 * @param mesh Lattice mesh
 * @param field lbField with population distribution
 */


void lbstream( latticeMesh* mesh, lbeField* field );

#endif // LBSTREAM_H
