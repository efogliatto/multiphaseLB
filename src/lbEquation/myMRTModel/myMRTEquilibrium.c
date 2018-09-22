#include <myMRTEquilibrium.h>
#include <basic.h>


void myMRTEquilibrium( latticeInfo* lattice, scalar T, scalar U[3], scalar alpha_1, scalar alpha_2, scalar* f ) {


    if( lattice->model == D2Q9 ) {


	// Equilibrium in moment space

	scalar n_eq[9];

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

	if( lattice->model == D3Q15 ) {


	    // Equilibrium in moment space

	    scalar n_eq[15];

	    n_eq[0]  = T;
	
	    n_eq[1]  = alpha_1 * T;

	    n_eq[2]  = alpha_2 * T;

	    n_eq[3]  =   T * U[0];

	    n_eq[4]  = -(T * U[0]);

	    n_eq[5]  =   T * U[1];

	    n_eq[6]  = -(T * U[1]);

	    n_eq[7]  =   T * U[2];

	    n_eq[8]  = -(T * U[2]);

	    n_eq[9]  = 0;

	    n_eq[10] = 0;

	    n_eq[11] = 0;

	    n_eq[12] = 0;

	    n_eq[13] = 0;

	    n_eq[14] = 0;
	    



	    // Equilibrium in population space

	    matVecMult(lattice->invM, n_eq, f, lattice->Q);

	    

	}
	
    }

}
