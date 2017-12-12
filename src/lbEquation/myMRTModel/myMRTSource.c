#include <macroFields.h>
#include <lbeField.h>
#include <latticeMesh.h>

void myMRTSource( struct latticeMesh* mesh, struct macroFields* mfields, double* Gamma, unsigned int id ) {

    unsigned int i, k;

    for( i = 0 ; i < mesh->lattice.Q ; i++ ) {

	double alpha = 0;

	for( k = 0 ; k < 3 ; k++ ) {

	    alpha += mesh->lattice.vel[i][k]   *   ( mfields->Fi[id][k]  +  (mfields->rho[id] - mesh->EOS.rho_0) * mesh->EOS._g[k] );

	}


	Gamma[i] = mesh->EOS._Cv * mfields->T[id] * mesh->lattice.omega[i] * alpha / mesh->lattice.cs2;

    }

}
