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

void myMRTEquilibrium( latticeInfo* lattice, double T, double U[3], double alpha_1, double alpha_2, double* f );

#endif // MYMRTEQUILIBRIUM_H
