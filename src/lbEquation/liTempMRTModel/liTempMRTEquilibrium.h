#ifndef LITEMPMRTEQUILIBRIUM_H
#define LITEMPMRTEQUILIBRIUM_H

#include <latticeInfo.h>

/**
 * @file liTempMRTEquilibrium.h
 * @author Ezequiel O. Fogliatto
 * @date 23 Apr 2018
 *
 * Equilibrium distribution in population space
 *
 * @param lattice Lattice info structure
 * @param T Macroscopic temperature at node
 * @param U Macroscopic velocity at node
 * @param alpha_1 Model constant
 * @param alpha_2 Model constant
 * @param f Distribution in population space. Must be allocated
 */

void liTempMRTEquilibrium( latticeInfo* lattice, scalar T, scalar U[3], scalar* f );

#endif // LITEMPMRTEQUILIBRIUM_H
