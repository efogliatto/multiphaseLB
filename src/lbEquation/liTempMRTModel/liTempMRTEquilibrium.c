#include <liTempMRTEquilibrium.h>
#include <basic.h>


void liTempMRTEquilibrium( latticeInfo* lattice, scalar T, scalar U[3], scalar* f ) {


    if( lattice->model == D2Q9 ) {


	// Equilibrium in moment space

	scalar n_eq[9];

	n_eq[0] = T;
	
    	n_eq[1] = -2.0 * T;
	
    	n_eq[2] = 2.0 * T;
	
    	n_eq[3] = T * U[0];
	
    	n_eq[4] = T * (-U[0]);
	
    	n_eq[5] = T * U[1];
	
    	n_eq[6] = T * (-U[1]);
	
    	n_eq[7] = 0;
	
    	n_eq[8] = 0;



	// Equilibrium in population space

	matVecMult(lattice->invM, n_eq, f, lattice->Q);
	

    }

    

}
