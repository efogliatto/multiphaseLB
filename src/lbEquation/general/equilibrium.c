#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <lbgkEquilibrium.h>

void equilibrium( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    
    // Apply equilibrium model according to field.colId

    unsigned int id;
    
    switch(field->colId) {

	
    // Li model. MRT version
	
    case 0:
	
	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    lbgkEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	}
	
	break;

	
    // Li model. SRT version
	
    case 1:
	
	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    lbgkEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	}
	
	break;
	
	

    // Li model. Temperature
	
    case 2:
	
	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    lbgkEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	}

	unsigned int k;

	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    field->value[id][k] = field->value[id][k] * mfields->Cv * mfields->T[id];
	    
	}

	
	break;
	


    default:
	break;
	
    }
    
}
