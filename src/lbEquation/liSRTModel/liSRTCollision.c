#include <liSRTCollision.h>
#include <liSRTEquilibrium.h>
#include <pseudoPot.h>

#include <stdlib.h>


void liSRTCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    // Indices
    unsigned int id, j, k;

    
    // Partial distributions
    double* feq   = (double*)malloc( mesh->lattice.Q * sizeof(double) );
    double* force = (double*)malloc( mesh->lattice.Q * sizeof(double) );

   
    // Total force
    double F[3];

    // Modified velocity
    double Vprime[3];
    

    // Move over points
    for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) {

	
	/* // Update tau value */
	/* updateTau(field, mfields->rho[id], mesh->lattice.Q);	 */
	

	// Compute equilibrium
	
	liSRTEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], feq );
	

	
	// Total force
	
	/* totalForce( mesh, F, mfields->rho, mfields->T, id ); */

	unsigned int jj;
	
	for( jj = 0 ; jj < 3 ; jj++ ) {

	    F[jj] = mfields->Fi[id][jj]  +   (mfields->rho[id] - mesh->EOS.rho_0) * mesh->EOS._g[jj];

	}




	

	
	// Potential
	
	double psi = potential( mesh, mfields->rho[id], mfields->T[id]);

	
	// Viscosity

	double nu = mesh->lattice.cs2 * (field->tau - 0.5);	

	
	// Update prime velocity
	Vprime[0] = mfields->U[id][0]  +  field->sigma * F[0] / (nu * psi * psi);
	Vprime[1] = mfields->U[id][1]  +  field->sigma * F[1] / (nu * psi * psi);
	Vprime[2] = mfields->U[id][2]  +  field->sigma * F[2] / (nu * psi * psi);	
	
	

	
	// Li forcing scheme. Move over velocities
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {


	    // Dot product 1. (e_k - Vprime) * F
	    double dot_1 = 0;	    
	    for( j = 0 ; j < 3 ; j++ ) {		
		dot_1 += ( mesh->lattice.vel[k][j] - Vprime[j] ) * F[j];
	    }


	    // Dot product 2. e_k * Vprime
	    double dot_2 = 0;	    
	    for( j = 0 ; j < 3 ; j++ ) {		
		dot_2 += mesh->lattice.vel[k][j] * Vprime[j];
	    }

	    // Dot product 3. dot_2 * e_k * F
	    double dot_3 = 0;	    
	    for( j = 0 ; j < 3 ; j++ ) {		
		dot_3 += (dot_2 * mesh->lattice.vel[k][j] ) * F[j];
	    }

	    force[k] = (1 - 0.5 / field->tau) * mesh->lattice.omega[k] * (dot_1  + dot_3 / mesh->lattice.cs2) / mesh->lattice.cs2;
	    
	}


	
	// Collide field
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    field->value[id][k] = field->value[id][k]   -   (1/field->tau) * ( field->value[id][k] - feq[k] )   +   force[k];

	}

    }


    // Deallocate memory
    free(feq);
    free(force);



    /* // Synchronize field */
    /* syncPdfField( &mesh->parallel, field->value, mesh->lattice.Q ); */


}
