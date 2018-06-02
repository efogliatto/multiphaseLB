#include <basic.h>
#include <myMRTCollision.h>
#include <myMRTSource.h>
#include <myMRTEquilibriumMS.h>



void myMRTCollision( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    // Indices
    
    unsigned int id, j, k;


    
    // Partial distributions
    
    double* n     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // m:  momentum space
    
    double* n_eq  = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // meq: equilibrium in momentum space   
    
    double* GammaHat = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // Source in population space

    double* aux_1  = (double*)malloc( mesh->lattice.Q * sizeof(double) );

    double* aux_2  = (double*)malloc( mesh->lattice.Q * sizeof(double) );

    unsigned int** nonZero  = (unsigned int**)malloc( 2 * sizeof(unsigned int*) );
    

    
    // Non-diagonal Q

    double** Q = matrixDoubleAlloc( mesh->lattice.Q, mesh->lattice.Q, 0 );

    double** Q_aux = matrixDoubleAlloc( mesh->lattice.Q, mesh->lattice.Q, 0 );  // Q_aux = I  -  0.5 * Q

    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	Q[k][k] = field->lbparam.myMRT.Lambda[k];

    }


    for( k = 0 ; k < 2 ; k++ ) {

	nonZero[k] = (unsigned int*)malloc( 2 * sizeof(unsigned int) );
	
    }
    

    nonZero[0][0] = 3;
    nonZero[0][1] = 4;
    nonZero[1][0] = 5;
    nonZero[1][1] = 6;

    

    if( mesh->lattice.Q == 9 ) {

    	Q[3][4] = Q[4][4]  *  ( Q[3][3]/2.0  - 1.0 );

    	Q[5][6] = Q[6][6]  *  ( Q[5][5]/2.0  - 1.0 );

    }


    for( j = 0 ; j < mesh->lattice.Q ; j++ ) {

	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    Q_aux[j][k] = -0.5 * Q[j][k];

	    if( j == k ) {

		Q_aux[j][k] = 1.0 + Q_aux[j][k];

	    }

	}

    }


    
    

    
    
    // Move over ALL points
    
    for( id = 0 ; id < mesh->mesh.nPoints ; id++ ) {
    /* for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) { */



	/* // Constant Lambda */
	
	/* if( field->tauModel == 2 ) { */
	    
	/*     Q[3][3] = 1 / ( 6.0 * field->lbParam.myMRT.lambda / (mfields->rho[id] * mesh->EOS.Cv * (4.0 + 3.0 * field->lbParam.myMRT.alpha_1 + 2.0 * field->lbParam.myMRT.alpha_2))  +  0.5); */

	/*     Q[5][5] = Q[3][3]; */

	/*     Q[3][4] = Q[4][4]  *  ( Q[3][3]/2.0  - 1.0 ); */

	/*     Q[5][6] = Q[6][6]  *  ( Q[5][5]/2.0  - 1.0 ); */


	/*     Q_aux[3][3] = 1.0 - 0.5 * Q[3][3]; */

	/*     Q_aux[5][5] = 1.0 - 0.5 * Q[5][5]; */

	/*     Q_aux[3][4] = -0.5 * Q[3][4]; */

	/*     Q_aux[5][6] = -0.5 * Q[5][6]; */

	/* } */
	
	

	// Equilibrium distribution in moment space

	myMRTEquilibriumMS( mesh, mfields, n_eq, field->lbparam.myMRT.alpha_1, field->lbparam.myMRT.alpha_2, id );
	
	
	
    	// Distribution in momentum space

    	matVecMult(mesh->lattice.M, field->value[id], n, mesh->lattice.Q);



	// Source in momentum space (heat sink, compression work and correction terms)

	myMRTSource(mesh, mfields, field, GammaHat, id);

	


	// First auxiliary distribution: n - n_eq

	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    aux_2[k] = n[k] - n_eq[k];

	}


	// aux_1 = Q * (n - n_eq)

	/* matVecMult(Q, aux_2, aux_1, mesh->lattice.Q); */

	sparseMatVecMult(Q, aux_2, aux_1, nonZero, mesh->lattice.Q, 2);


	


	// Second auxiliary distribution: (I  -  0.5 * Q) * GammaHat
	
	/* matVecMult(Q_aux, GammaHat, aux_2, mesh->lattice.Q); */

	sparseMatVecMult(Q_aux, GammaHat, aux_2, nonZero, mesh->lattice.Q, 2);
	
	
	
	
    	// Collision in momentum space
	
    	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

    	    n[k] = n[k] - aux_1[k] + aux_2[k];
	    
    	}

	
	
    	// Back to population space
	
    	matVecMult(mesh->lattice.invM, n, field->value[id], mesh->lattice.Q);

	
    }

    

    // Deallocate memory

    free(n);

    free(n_eq);

    free(GammaHat);

    free(aux_1);

    free(aux_2);

    
    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	free( Q[k] );

	free( Q_aux[k] );

    }

    free(Q);

    free(Q_aux);


    for( k = 0 ; k < 2 ; k++ ) {

	free( nonZero[k] );

    }

    free(nonZero);
    

    
}
