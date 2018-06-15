#ifndef MYMRTEQUILIBRIUM_H
#define MYMRTEQUILIBRIUM_H

#include <latticeInfo.h>

/**
 * @file myMRTEquilibrium.h
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

void myMRTEquilibrium( latticeInfo* lattice, scalar T, scalar U[3], scalar alpha_1, scalar alpha_2, scalar* f );

#endif // MYMRTEQUILIBRIUM_H
