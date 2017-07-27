#include <latticeMesh.h>
#include <macroFields.h>
#include <vectorDivergence.h>

void compWork( struct latticeMesh* mesh, struct macroFields* mfields ) {

    
    unsigned int id;

    double divU;

    double phi;

    
    for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) {


	// Compute divergence of velocity field

	divU = vectorDivergence( mesh, mfields->U, id );

	

	// Compute phi term

	phi = -mfields->T[id] * mfields->rho[id] * mesh->EOS._R / ( mesh->EOS._M - mesh->EOS._b * mfields->rho[id] );


	
	// Compute compression work
	
	mfields->phiDivU[id] = phi * divU;
	

    }

    
}
