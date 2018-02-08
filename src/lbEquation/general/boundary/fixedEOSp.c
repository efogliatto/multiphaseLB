#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <liMRTEquilibrium.h>
#include <pseudoPot.h>


void fixedEOSp( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) {



    /* if(  ( field->colId == 2 ) ||  ( field->colId == 3 )  ){ */

	
	unsigned int i;

	
    
	// Move over boundary elements

	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {


	    // Point local index
	    
	    unsigned int id = mesh->mesh.bd.bdPoints[bid][i];


	    
	    // EOS fixed pressure value, using refence values for density and temperature

	    double p_bd = p_eos(&mesh->EOS, field->boundary[bid].vectorVal[0], field->boundary[bid].vectorVal[1]);

	    

	    // New density that matches p_bd
	    
	    double newRho = 0, rho = mfields->rho[id];

	    while(  abs(newRho - rho) / rho > 1e-06  ) {

		newRho = rho;

		rho = rhoFromEOS(&mesh->EOS, rho, mfields->T[id], p_bd);

	    }


	    

	    // Assign equilibrium distribution using new density

	    mfields->rho[id] = rho;

	    liMRTEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	
	

	}




    /* } */


    /* else { */

    /* 	printf("\n  [ERROR]  Unable to apply boundary condition on temperature\n\n"); */

    /* 	exit(1); */

    /* } */
    

}
