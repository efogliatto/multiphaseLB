#include <basic.h>
#include <myMRTCollision.h>
#include <myMRTSource.h>
#include <myMRTEquilibriumMS.h>



void myMRTCollision( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    // Indices
    
    uint id, j, k;


    
    // Partial distributions
    
    scalar* n     = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // m:  momentum space
    
    scalar* n_eq  = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // meq: equilibrium in momentum space   
    
    scalar* GammaHat = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // Source in population space

    scalar* aux_1  = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );

    scalar* aux_2  = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );

    uint** nonZero;
    

    
    // Non-diagonal Q

    scalar** Q = matrixDoubleAlloc( mesh->lattice.Q, mesh->lattice.Q, 0 );

    scalar** Q_aux = matrixDoubleAlloc( mesh->lattice.Q, mesh->lattice.Q, 0 );  // Q_aux = I  -  0.5 * Q

    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	Q[k][k] = field->lbparam.myMRT.Lambda[k];

    }



    // Non-zero off diagonal elements from Q


    if( mesh->lattice.model == D2Q9 ) {

	nonZero = (uint**)malloc( 2 * sizeof(uint*) );
	
	for( k = 0 ; k < 2 ; k++ ) {

	    nonZero[k] = (uint*)malloc( 2 * sizeof(uint) );
	
	}
    

	nonZero[0][0] = 3;
	nonZero[0][1] = 4;
	nonZero[1][0] = 5;
	nonZero[1][1] = 6;


    	Q[3][4] = Q[4][4]  *  ( Q[3][3]/2.0  - 1.0 );

    	Q[5][6] = Q[6][6]  *  ( Q[5][5]/2.0  - 1.0 );	

    }


    else {

	if( mesh->lattice.model == D3Q15 ) {

	    nonZero = (uint**)malloc( 3 * sizeof(uint*) );
	
	    for( k = 0 ; k < 3 ; k++ ) {

		nonZero[k] = (uint*)malloc( 3 * sizeof(uint) );
	
	    }
    

	    nonZero[0][0] = 3;
	    nonZero[0][1] = 4;
	    nonZero[1][0] = 5;
	    nonZero[1][1] = 6;
	    nonZero[2][0] = 7;
	    nonZero[2][1] = 8;

	    Q[3][4] = Q[4][4]  *  ( Q[3][3]/2.0  - 1.0 );

	    Q[5][6] = Q[6][6]  *  ( Q[5][5]/2.0  - 1.0 );

	    Q[7][8] = Q[8][8]  *  ( Q[7][7]/2.0  - 1.0 );

	}

    }

    


    // Q_aux = I  -  0.5 * Q

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

	switch( mesh->lattice.model ) {

	case D2Q9:

	    sparseMatVecMult(Q_aux, GammaHat, aux_2, nonZero, mesh->lattice.Q, 2);

	    break;


	case D3Q15:

	    sparseMatVecMult(Q_aux, GammaHat, aux_2, nonZero, mesh->lattice.Q, 3);

	    break;	    

	}
	
	
	
	
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

    if(mesh->lattice.model == D3Q15) {

	free( nonZero[2] );

    }

    free(nonZero);
    

    
}
