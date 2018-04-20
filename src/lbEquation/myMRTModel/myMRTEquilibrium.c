#include <latticeInfo.h>
#include <basic.h>


void myMRTEquilibrium( latticeInfo* lattice, double T, double U[3], double alpha_1, double alpha_2, double* f ) {


    if(   (lattice->Q == 9)   &&   (lattice->d == 2)   ) {


	// Equilibrium in moment space

	double n_eq[9];

	n_eq[0] = T;
	
    	n_eq[1] = alpha_1 * T;
	
    	n_eq[2] = alpha_2 * T;
	
    	n_eq[3] = T * U[0];
	
    	n_eq[4] = T * (-U[0]);
	
    	n_eq[5] = T * U[1];
	
    	n_eq[6] = T * (-U[1]);
	
    	n_eq[7] = 0;
	
    	n_eq[8] = 0;



	// Equilibrium in population space

	matVecMult(lattice->invM, n_eq, f, lattice->Q);
	

    }

    else {


    }

}
