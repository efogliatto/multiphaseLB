#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void bounceBack( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) {

    unsigned int i, k;
    

    // Move over boundary elements
    
    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	int id = mesh->mesh.bd.bdPoints[bid][i];

	
	// Move over lattice velocities
	
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    if ( mesh->mesh.nb[id][k] == -1 ) {

		field->value[id][k] = field->value[id][mesh->lattice.reverse[k]];

		/* if ( mesh->mesh.nb[id][lattice->reverse[k]] == -1 ) { */

		/*     alpha = k; */
		    
		/* } */

	    }

	}




	/* // Apply corner correction */
	/* if(alpha != 0) { */


	/*     /\* // Compute extrapolated density *\/ */
	/*     /\* double rho = 0; *\/ */
	/*     /\* int extra = 0; *\/ */

	/*     /\* for( k = 0 ; k < lattice->Q ; k++ ) { *\/ */
		
	/*     /\* 	if ( nb[id][k] != -1  ) { *\/ */

	/*     /\* 	    rho += mfields->rho[ nb[id][k] ]; *\/ */
	/*     /\* 	    extra++; *\/ */
		    
	/*     /\* 	} *\/ */
		    
	/*     /\* } *\/ */

	/*     /\* rho = rho / extra; *\/ */


	/*     // Method 1. Complete density and velocity */

	/*     /\* // Compute partial sums *\/ */
	/*     /\* double partial_1 = 0, partial_2 = 0; *\/ */

	/*     /\* for( k = 0 ; k < lattice->Q ; k++ ) { *\/ */

	/*     /\* 	if(  ( k != alpha )   &&   ( k != beta )  ) { *\/ */

	/*     /\* 	    partial_1 += field->value[id][k]; *\/ */

	/*     /\* 	    partial_2 += lattice->vel[k][0] * field->value[id][k]; *\/ */

	/*     /\* 	} *\/ */

	/*     /\* } *\/ */



	/*     /\* // Update distribution values *\/ */
	/*     /\* field->value[id][alpha] = 0.5 * ( -partial_2 / lattice->vel[alpha][0] + rho - partial_1  ); *\/ */
	/*     /\* field->value[id][beta]  = rho - partial_1 - field->value[id][alpha]; *\/ */





	/*     /\* // Method 2. Equilibrium values *\/ */

	/*     /\* for( k = 0 ; k < lattice->Q ; k++ ) { *\/ */

	/*     /\* 	field->value[id][k] = lattice->omega[k] * rho; *\/ */
		
	/*     /\* } *\/ */
	    

	    
	/* } */

	

    }

}
